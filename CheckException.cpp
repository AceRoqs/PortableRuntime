#include "PreCompile.h"
#include "CheckException.h"     // Pick up forward declarations to ensure correctness.
#include "Tracing.h"

namespace PortableRuntime
{

namespace Detail
{

// TODO: Consider DebugBreak in log?
// TODO: Add logging in catch statements to pair with the throws?  i.e. "Recovered exception, etc."
void throw_exception(const std::string& message)
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
    dprintf((message + "\n").c_str());
    throw std::exception(message.c_str());
}

}

}

