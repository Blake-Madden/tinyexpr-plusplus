#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/catch_session.hpp>

int main(int argc, char** argv)
    {
    Catch::Session session;

    session.applyCommandLine(argc, argv);

    session.run();

    return EXIT_SUCCESS;
    }