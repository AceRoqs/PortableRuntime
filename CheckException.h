#pragma once

namespace PortableRuntime
{

// TODO: Move implementation to .cpp file.
// TODO: Move this to a detail namespace, and have client code use the macro to avoid unnecessary evaluaton of string.
inline void check_exception(bool result, const char* message)
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
        throw std::exception(message);
    }
}

#define CHECK_EXCEPTION(zzz_expr, zzz_str) { \
    const bool zzz_val = zzz_expr; \
    if(!zzz_val) \
    { \
        PortableRuntime::check_exception(zzz_val, zzz_str); \
    } \
    _Analysis_assume_(zzz_expr); \
}

}

