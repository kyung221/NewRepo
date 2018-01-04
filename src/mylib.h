#ifndef _SCONE_H_
#define _SCONE_H_
#include <cstdint> // stdint.h

namespace Scone
{

// typedef std::uint8_t byte;
using byte = std::uint8_t;

int version();

// 다른 라이브러리 로드/정적 변수 초기화
bool init();
// 동적 메모리를 할당 + 초기화
void reserve();
// 점유한 동적 메모리들을 해제
void release();

int fillData(byte *memory);

} // namespace Scone

#endif // _SCONE_H_
