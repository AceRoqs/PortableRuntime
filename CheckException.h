#pragma once

// TODO: 2016: Remove this.
#pragma message("***************** Remove this.")
#include <functional>

namespace PortableRuntime
{

class Exception : public std::exception
{
protected:
    explicit Exception(_In_z_ const char* file_name, int line) noexcept;

    // Use a shared_ptr to minimize the memory cost when copying an exception during unwind.
    // If m_what is nullptr, then there was a problem during construction, very likely a bad_alloc.
    mutable std::shared_ptr<std::string> m_what;

    // File and line saved to provide information in case m_what can't be created.
    const char* m_file_name{};
    const int m_line{-1};

    // True if m_what already has file and line information.
    mutable bool m_formatted{};

public:
    explicit Exception(const std::string& message, _In_z_ const char* file_name, int line) noexcept;
    virtual const char* what() const noexcept override;

    void hide_details() const noexcept;
};

// TODO: 2016: Rework this - the intent is to catch exceptions of a function passed in,
// but CHECK_ERROR pre-executes the function.
inline void friendly_exception(const std::function<void(void)>& lambda)
{
    try
    {
        lambda();
    }
    catch(const PortableRuntime::Exception& ex)
    {
        ex.hide_details();
        throw;
    }
}

class Error : public Exception
{
public:
    explicit Error(const std::string& message, _In_z_ const char* file_name, int line) noexcept;
};

// CHECK_EXCEPTION macro allows for usage of __FILE__ and __LINE__
// and avoids evaluation of string in success case.
// NOTE: It is assumed that __FILE__ is UTF-8 or at least ASCII.  Under MSVC,
// this expands based on code page, so for correctness, filenames must be ASCII only.
// TODO: 2016: Document this guideline/restriction somewhere.
#define CHECK_EXCEPTION(zzz_expr, zzz_message)                                  \
[&]()                                                                           \
{                                                                               \
    const bool zzz_val = (zzz_expr);                                            \
    if(!zzz_val)                                                                \
    {                                                                           \
        throw ::PortableRuntime::Exception((zzz_message), __FILE__, __LINE__);  \
    }                                                                           \
}()

#define CHECK_ERROR(zzz_expr, zzz_message)                                      \
[&]()                                                                           \
{                                                                               \
    const bool zzz_val = (zzz_expr);                                            \
    if(!zzz_val)                                                                \
    {                                                                           \
        throw ::PortableRuntime::Error((zzz_message), __FILE__, __LINE__);      \
    }                                                                           \
}()

}

