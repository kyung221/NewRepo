#include "catch.hpp"
#include <cstdlib>

// 전용 헤더파일
#include <dlfcn.h>
#include "mylib.h"

SCENARIO("Init")
{

    using namespace Scone;
    // 초기화를 깜빡했음
    GIVEN("Init skipped")
    {
        WHEN("Try Release")
        {
            REQUIRE_NOTHROW(release());
        }
        //fillData test
        GIVEN("Bad argument")
        {
            WHEN("nullptr")

            {
                THEN("return negative")
                {
                    REQUIRE(fillData(nullptr) < 0);
                }
            }
        }

        GIVEN("Good argument")
        {
            WHEN("empty array")
            {
                byte input[10]{};

                REQUIRE(fillData(input) < 0);
            }
        }
    }

    init();
    // 초기화를 제대로 했음
    GIVEN("Init OK")
    {
        WHEN("Init Again")
        {
            THEN("No effect")
            {
                init();
            }
        }
        reserve();

        WHEN("Try fillData")
        {
            THEN("Success with args")
            {
                byte array[10]{};

                REQUIRE((void *)array != nullptr);
                REQUIRE(fillData(array) >= 0);
            }

            THEN("Fail with bad args")
            {
                REQUIRE(fillData(nullptr) < 0);
            }
        }

        WHEN("Try Release")
        {
            release();

            THEN("Library shouldn't work")
            {
                REQUIRE(fillData(nullptr) < 0);
            }
        }
    }
}