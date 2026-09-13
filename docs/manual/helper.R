render_grviz <- function(graph) {
  if (knitr::is_html_output()) {
    graph
  } else {
    # Each chapter is knitted in its own R subprocess, whose tempfile()
    # directory is gone by the time the final PDF is built from the
    # combined chapters. Make the image live somewhere persistent.
    svg_text <- DiagrammeRsvg::export_svg(graph)

    out_dir <- file.path(".quarto", "grviz-cache")
    if (!dir.exists(out_dir)) {
      dir.create(out_dir, recursive = TRUE)
    }
    png_file <- file.path(out_dir, paste0(digest::digest(svg_text), ".png"))

    # Graphviz's declared width/height attributes don't always match the
    # svg's own viewBox aspect ratio. rsvg sizes off those attributes by
    # default, which distorts the raster. Derive the true aspect ratio
    # from the viewBox instead and render at 3x for print sharpness.
    view_box <- regmatches(
      svg_text,
      regexec('viewBox="[0-9.]+ [0-9.]+ ([0-9.]+) ([0-9.]+)"', svg_text)
    )[[1]]
    box_width <- as.numeric(view_box[2])
    box_height <- as.numeric(view_box[3])

    rsvg::rsvg_png(
      charToRaw(svg_text),
      png_file,
      width = round(box_width * 3),
      height = round(box_height * 3)
    )

    knitr::include_graphics(png_file)
  }
}