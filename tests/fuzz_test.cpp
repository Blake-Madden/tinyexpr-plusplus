/* - Place input seed files into 'FuzzCorpus' folder.
   - Complile and run from this folder:

   clang -g -O1 -std=c++17 -fsanitize=fuzzer,address fuzz_test.cpp ../tinyexpr.cpp -o fuzzer
   ./fuzzer FuzzCorpus
*/

#include "../tinyexpr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
  {
  te_parser tep;
  tep.compile(std::string(reinterpret_cast<const char*>(Data), Size).c_str());
  return 0;
  }
