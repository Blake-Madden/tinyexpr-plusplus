#!/usr/bin/env python3
# clang_tidy_html_report.py
# Parse clang-tidy stdout logs -> rich HTML (filterable)
# - Filters out "note" severity entirely
# - Suppresses checks/messages via hard-coded sets and env overrides
# - Emits post-filter counts (--counts) and can fail the process (--fail-on)

import re, sys, html, argparse, pathlib, os, json
from string import Template
from collections import defaultdict, Counter

# ---------- configurable suppression ----------
# Hide diagnostics whose check name exactly matches any of these:
SUPPRESS_CHECKS = {
    "IgnoreClassesWithAllMemberVariablesBeingPublic",
    "clang-diagnostic-error",
    "clang-analyzer-optin.cplusplus.VirtualCall",
}
# Hide diagnostics whose *message* contains any of these substrings:
SUPPRESS_MSG_SUBSTR = {
    "IgnoreClassesWithAllMemberVariablesBeingPublic",
    "use of undeclared identifier",
    "file not found",
    "unknown type name",
    "no matching function for call to",
}
# Optional env overrides (comma-separated lists)
SUPPRESS_CHECKS |= {s.strip() for s in os.getenv("CT_SUPPRESS_CHECKS", "").split(",") if s.strip()}
SUPPRESS_MSG_SUBSTR |= {s.strip() for s in os.getenv("CT_SUPPRESS_MSG_SUBSTR", "").split(",") if s.strip()}
# ------------------------------------------------

ROW_RE = re.compile(
    r'^(?P<file>[^:\n]+):(?P<line>\d+):(?P<col>\d+):\s+'
    r'(?P<sev>warning|error|note):\s+'
    r'(?P<msg>.*?)(?:\s\[(?P<check>[^\]]+)\])?\s*$'
)

HTML = Template("""<!doctype html>
<html lang="en"><head>
<meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<title>Clang-Tidy Report</title>
<style>
  :root{--bg:#0b0d10;--fg:#e6edf3;--muted:#9aa7b1;--row:#11151a;--accent:#2f81f7;--warn:#f5a623;--err:#ff4d4f}
  body{background:var(--bg);color:var(--fg);font:14px/1.45 ui-sans-serif,system-ui,-apple-system,Segoe UI,Roboto,Arial,sans-serif;margin:24px}
  h1{margin:0 0 16px 0;font-size:22px}
  .muted{color:var(--muted)}
  .chips{display:flex;gap:8px;flex-wrap:wrap;margin:6px 0 16px 0}
  .chip{background:#1a2129;border:1px solid #223041;padding:4px 10px;border-radius:999px;font-size:12px}
  .chip strong{color:var(--fg)}
  .filters{display:flex;gap:12px;margin:14px 0 18px 0;align-items:center}
  select,input[type="search"]{background:#0f141a;color:var(--fg);border:1px solid #223041;padding:6px 10px;border-radius:8px}
  table{width:100%;border-collapse:collapse}
  th,td{text-align:left;padding:10px 8px;border-bottom:1px solid #1f2630}
  tr{background:var(--row)} tr:hover{background:#141a22}
  th{position:sticky;top:0;background:#0e141b;z-index:2}
  code{background:#0f141a;padding:2px 6px;border-radius:6px}
  .sev-warning{color:var(--warn)} .sev-error{color:var(--err)}
  .footer{margin-top:18px;font-size:12px;color:var(--muted)} .nowrap{white-space:nowrap}
</style>
</head><body>
  <h1>Clang-Tidy Report</h1>
  <div class="chips">
    <div class="chip"><strong>Total</strong> $total</div>
    <div class="chip"><span class="sev-error"><strong>Errors</strong></span> $n_err</div>
    <div class="chip"><span class="sev-warning"><strong>Warnings</strong></span> $n_warn</div>
    <div class="chip"><strong>Files</strong> $files_count</div>
    <div class="chip"><strong>Checks</strong> $checks_count</div>
  </div>

  <div class="filters">
    <label>Severity:
      <select id="sev">
        <option value="">All</option>
        <option value="error">Error</option>
        <option value="warning">Warning</option>
      </select>
    </label>
    <label>Check:
      <select id="check">
        <option value="">All</option>
        $check_opts
      </select>
    </label>
    <label class="nowrap">Search:
      <input id="q" type="search" placeholder="file / message contains…">
    </label>
  </div>

  <table id="tbl">
    <thead><tr>
      <th class="nowrap">Severity</th>
      <th>Check</th>
      <th>Message</th>
      <th>File</th>
      <th class="nowrap">Line:Col</th>
    </tr></thead>
    <tbody>
      $rows
      $empty_row
    </tbody>
  </table>

  <div class="section">
    <h2>By Check</h2>
    <table>
      <thead><tr><th>Check</th><th>Count</th><th>Examples</th></tr></thead>
      <tbody>$by_check_rows</tbody>
    </table>
  </div>

  <div class="footer muted">Config: .clang-tidy • Generated from clang-tidy logs</div>

<script>
(() => {
  const sevSel=document.getElementById('sev');
  const chkSel=document.getElementById('check');
  const q=document.getElementById('q');
  const rows=Array.from(document.querySelectorAll('#tbl tbody tr[data-sev]'));
  function matches(r){
    const s=sevSel.value,c=chkSel.value,t=q.value.toLowerCase().trim();
    if(s && r.dataset.sev!==s) return false;
    if(c && r.dataset.check!==c) return false;
    if(t){const hay=(r.dataset.file+' '+r.dataset.msg).toLowerCase(); if(!hay.includes(t)) return false;}
    return true;
  }
  function apply(){
    let any=false;
    rows.forEach(r=>{const ok=matches(r); r.style.display=ok?'':'none'; if(ok) any=true;});
    document.getElementById('empty')?.remove();
    if(!any){
      const tr=document.createElement('tr'); tr.id='empty';
      tr.innerHTML=`<td colspan="5" class="muted">No rows match.</td>`;
      document.querySelector('#tbl tbody').appendChild(tr);
    }
  }
  [sevSel,chkSel].forEach(e=>e.addEventListener('change',apply));
  q.addEventListener('input',apply);
})();
</script>
</body></html>
""")

def parse_logs(paths):
    entries=[]
    for p in paths:
        try:
            text=pathlib.Path(p).read_text(encoding='utf-8', errors='replace').splitlines()
        except Exception:
            continue
        for line in text:
            m=ROW_RE.match(line.strip())
            if not m:
                continue
            d=m.groupdict()
            entries.append({
                'file': d['file'],
                'line': int(d['line']),
                'col': int(d['col']),
                'sev': d['sev'],
                'msg': d['msg'],
                'check': d.get('check') or '',
            })
    return entries

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--logs", nargs='+', required=True, help="One or more clang-tidy *.txt logs")
    ap.add_argument("--out", required=True, help="Output HTML path")
    # counts + failure control
    ap.add_argument("--counts", help="Write post-filter counts to this JSON file")
    ap.add_argument("--fail-on", choices=["none", "errors", "warnings"], default="none",
                    help="Exit non-zero if errors/warnings remain after filters")

    a=ap.parse_args()

    items=parse_logs(a.logs)

    # 1) drop notes entirely
    items=[it for it in items if it['sev'] != 'note']

    # 2) apply check/message suppressions
    def _suppressed(it):
        if it['check'] in SUPPRESS_CHECKS:
            return True
        msg = it['msg']
        for sub in SUPPRESS_MSG_SUBSTR:
            if sub and sub in msg:
                return True
        return False
    items=[it for it in items if not _suppressed(it)]

    # sort with errors first, then warnings, then by file/loc/check
    items.sort(key=lambda x: (x['sev']!='error', x['sev']!='warning', x['file'], x['line'], x['col'], x['check']))

    by_check=defaultdict(list)
    files=set()
    sev_ct=Counter()
    for it in items:
        by_check[it['check']].append(it)
        files.add(it['file'])
        sev_ct[it['sev']]+=1

    esc=lambda s: html.escape(str(s or ""))

    row_html=[]
    for it in items:
        row_html.append(
            f"<tr data-sev='{esc(it['sev'])}' data-check='{esc(it['check'])}' "
            f"data-file='{esc(it['file'])}' data-msg='{esc(it['msg'])}'>"
            f"<td class='sev-{esc(it['sev'])}'>{esc(it['sev'])}</td>"
            f"<td><code>{esc(it['check']) or '—'}</code></td>"
            f"<td>{esc(it['msg'])}</td>"
            f"<td class='nowrap'>{esc(it['file'])}</td>"
            f"<td class='nowrap'>{it['line']}:{it['col']}</td>"
            f"</tr>"
        )
    empty_row = "" if row_html else "<tr id='empty'><td colspan='5' class='muted'>No diagnostics.</td></tr>"

    check_opts="\n".join(
        f"<option value='{esc(k)}'>{esc(k)} ({len(v)})</option>"
        for k,v in sorted(by_check.items(), key=lambda kv: (-len(kv[1]), kv[0])) if k
    )

    by_check_rows=[]
    for chk,lst in sorted(by_check.items(), key=lambda kv: (-len(kv[1]), kv[0])):
        examples="".join(
            f"<div><span class='nowrap'>{esc(it['file'])}:{it['line']}</span> — {esc(it['msg'])}</div>"
            for it in lst[:3]
        )
    # NOTE: keep by_check_rows even if empty
        by_check_rows.append(f"<tr><td><code>{esc(chk) or '—'}</code></td><td>{len(lst)}</td><td>{examples}</td></tr>")
    by_check_html = "\n".join(by_check_rows) if by_check_rows else "<tr><td colspan='3' class='muted'>No diagnostics.</td></tr>"

    html_out = HTML.substitute(
        total=len(items),
        n_err=sev_ct['error'],
        n_warn=sev_ct['warning'],
        files_count=len(files),
        checks_count=sum(1 for k in by_check if k),
        check_opts=check_opts,
        rows="\n".join(row_html),
        empty_row=empty_row,
        by_check_rows=by_check_html
    )

    outp=pathlib.Path(a.out)
    outp.parent.mkdir(parents=True, exist_ok=True)
    outp.write_text(html_out, encoding='utf-8')

    # write counts + optional failure
    if a.counts:
        with open(a.counts, "w", encoding="utf-8") as f:
            json.dump({
                "errors": int(sev_ct["error"]),
                "warnings": int(sev_ct["warning"]),
                "total": int(len(items)),
            }, f)

    if a.fail_on == "errors" and sev_ct["error"] > 0:
        sys.exit(1)
    if a.fail_on == "warnings" and (sev_ct["error"] > 0 or sev_ct["warning"] > 0):
        sys.exit(1)

if __name__=="__main__":
    main()
