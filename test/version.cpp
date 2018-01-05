#include "catch.hpp"

#include "mylib.h"

const char *Tag = "[Basic]";

using namespace std;

TEST_CASE("Version", Tag)
{
    using namespace Scone;

    REQUIRE(version() > 0);
}
