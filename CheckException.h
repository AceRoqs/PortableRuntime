#pragma once

namespace PortableRuntime
{

class Exception : public std::exception
{
    std::shared_ptr<std::string> m_what;

public:
    explicit Exception(const std::string& message);
    virtual const char* what() const noexcept override;
};

namespace Detail
{

void throw_exception(const std::string& message, _In_z_ const char* file_name, int line);

}

// CHECK_EXCEPTION macro allows for usage of __FILE__ and __LINE__
// and avoid evaluation of string in success case.
#define CHECK_EXCEPTION(zzz_expr, zzz_message) { \
    const bool zzz_val = (zzz_expr); \
    if(!zzz_val) \
    { \
        PortableRuntime::Detail::throw_exception((zzz_message), __FILE__, __LINE__); \
    } \
    _Analysis_assume_((zzz_expr)); \
}

}

