#pragma once

namespace PortableRuntime
{

namespace Detail
{

void throw_exception(const std::string& message);

}

// CHECK_EXCEPTION macro allows for usage of __FILE__ and __LINE__
// and avoid evaluation of string in success case.
#define CHECK_EXCEPTION(zzz_expr, zzz_str) { \
    const bool zzz_val = (zzz_expr); \
    if(!zzz_val) \
    { \
        PortableRuntime::Detail::throw_exception((zzz_str)); \
    } \
    _Analysis_assume_((zzz_expr)); \
}

}

