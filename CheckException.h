#pragma once

namespace PortableRuntime
{

namespace Detail
{

// TODO: Move implementation to .cpp file.
// TODO: Add logging.  TODO: Consider DebugBreak in log?
// TODO: Add logging in catch statements to pair with the throws?  i.e. "Recovered exception, etc."
inline void check_exception(bool result, const std::string& message)
{
    if(!result)
    {
#if defined(_MSC_VER) && !defined(NDEBUG)
        // Work around MSVC issue where the abort() message box is displayed instead of the assert messagebox.
        // This makes the abort/retry/ignore of the dialog not work for the "ignore" case.  Since the abort dialog is called
        // even for console apps where blocking for a GUI response is not ideal, just mimic the behavior as it is no worse.
        // This also has the nice side effect of printing error information to the debugger window.
        _set_error_mode(_OUT_TO_MSGBOX);
#endif
        // Force break.
        assert(false);
        throw std::exception(message.c_str());
    }
}

}

// CHECK_EXCEPTION macro allows for usage of __FILE__ and __LINE__
// and avoid evaluation of string in success case.
#define CHECK_EXCEPTION(zzz_expr, zzz_str) { \
    const bool zzz_val = (zzz_expr); \
    if(!zzz_val) \
    { \
        PortableRuntime::Detail::check_exception(zzz_val, (zzz_str)); \
    } \
    _Analysis_assume_(zzz_expr); \
}

}

