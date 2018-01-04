
// 전용 헤더파일
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("Check")
{
    // 인자 개수 확인
    // 입력(인자)) 값 출력

    // 1. 라이브러리 파일의 존재
    // 2. 라이브러리 내 함수의 존재

    int argc;
    char *argv[3];

    argc = 3;
    argv[0] = "Check";
    argv[1] = "../libHello.so";
    argv[2] = "_ZN5Scone7versionEv";

    const char *libName = argv[1];
    const char *funcName = argv[2];

    REQUIRE(argc == 3);

    REQUIRE(argv[1]);
    REQUIRE(argv[2]);

    CAPTURE(libName);
    CAPTURE(funcName);

    void *handle = dlopen(libName, RTLD_LAZY);
    REQUIRE(handle != nullptr);

    void *pFunc = dlsym(handle, funcName);
    dlclose(handle);

    REQUIRE(pFunc != nullptr);
}
