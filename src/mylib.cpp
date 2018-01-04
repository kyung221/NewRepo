#include "mylib.h"

namespace Scone
{

int version()
{
    return 1;
}

// 다른 라이브러리 로드/정적 변수 초기화
bool init()
{
    return true;
}
// 동적 메모리를 할당 + 초기화
void reserve() {}
// 점유한 동적 메모리들을 해제
void release() {}

int fillData(byte *memory)
{
    if (memory != nullptr)
        return *memory;
    else
        return -1;
}

} // Scone
