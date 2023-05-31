// This is mostly used as a CMake project used for code analysis.

#include "../../tinyexpr.h"
#include <iostream>

int main(int argc, char *argv[])
    {
    te_parser tep;
    const char *c = "sqrt(5^2+7^2+11^2+(8-2)^2)";
    double r = tep.evaluate(c);
    std::cout << "The expression:\n\t" <<
        c << "\nevaluates to:\n\t" << r << "\n";
    return EXIT_SUCCESS;
    }
