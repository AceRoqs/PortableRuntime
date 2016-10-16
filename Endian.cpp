#include "PreCompile.h"
#include "Endian.h"         // Pick up forward declarations to ensure correctness.

/*
For actual swaps, Visual C++ defines the following in intrin.h:
    _byteswap_ushort
    _byteswap_ulong
    _byteswap_uint64
GCC defines similar intrinsics:
    __builtin_bswap32
    __builtin_bswap64
    (16-bit swap is simply a bit rotate)
Clang doesn't appear to have intrinsics for this.

To detect endianness at runtime, use the following.  The compiler should
be able to optimize the function completely away, but check the assembly
to be sure.

bool is_big_endian()
{
    unsigned int x = 1;
    return *reinterpret_cast<uint8_t*>(&x) == 0;
}
*/

#ifndef PORTABLE_RUNTIME_USE_BIG_ENDIAN
#define PORTABLE_RUNTIME_USE_BIG_ENDIAN 0
#endif
constexpr bool use_big_endian = PORTABLE_RUNTIME_USE_BIG_ENDIAN;

namespace PortableRuntime
{

// Change byte order from big to little or little to big.
static uint16_t uint16_swap(uint16_t value) noexcept
{
#ifdef _MSC_VER
    return _byteswap_ushort(value);
#else
    return ((value >> 8) & 0x00ff) | ((value << 8) & 0xff00);
#endif
}

static uint32_t uint32_swap(uint32_t value) noexcept
{
#ifdef _MSC_VER
    return _byteswap_ulong(value);
#else
    return ((value >> 24) & 0x000000ff) | ((value >> 8) & 0x0000ff00) | ((value << 8) & 0x00ff0000) | ((value << 24) & 0xff000000);
#endif
}

// Change byte order from big/little to native format.
uint16_t lswap16(uint16_t value) noexcept
{
    if(use_big_endian)
    {
        return uint16_swap(value);
    }

    return value;
}

uint16_t bswap16(uint16_t value) noexcept
{
    if(use_big_endian)
    {
        return value;
    }

    return uint16_swap(value);
}

uint32_t lswap32(uint32_t value) noexcept
{
    if(use_big_endian)
    {
        return uint32_swap(value);
    }

    return value;
}

uint32_t bswap32(uint32_t value) noexcept
{
    if(use_big_endian)
    {
        return value;
    }

    return uint32_swap(value);
}

}

