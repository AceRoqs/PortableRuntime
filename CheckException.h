#pragma once

namespace PortableRuntime
{

class Exception : public std::exception
{
    // Use a shared_ptr to minimize the memory cost when copying an exception during unwind.
    // If m_what is nullptr, then there was a problem during construction, very likely a bad_alloc.
    std::shared_ptr<std::string> m_what;

    // File and line saved to provide information in case m_what can't be created.
    const char* m_file;
    int m_line;

public:
    explicit Exception(const std::string& message, _In_z_ const char* file_name, int line);
    virtual const char* what() const noexcept override;
};

// CHECK_EXCEPTION macro allows for usage of __FILE__ and __LINE__
// and avoids evaluation of string in success case.
#define CHECK_EXCEPTION(zzz_expr, zzz_message) { \
    const bool zzz_val = (zzz_expr); \
    if(!zzz_val) \
    { \
        throw ::PortableRuntime::Exception((zzz_message), __FILE__, __LINE__); \
    } \
    _Analysis_assume_((zzz_expr)); \
}

}

