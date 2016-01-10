#include "PreCompile.h"
#include "Tracing.h"        // Pick up forward declarations to ensure correctness.

namespace PortableRuntime
{

static void null_dprintf(_In_z_ const char* format) noexcept
{
    (void)(format); // Unreferenced parameter.
}

static Output_dprintf output_dprintf = null_dprintf;

void dprintf(_In_z_ const char* format, ...) noexcept
{
#ifndef NDEBUG
    char print_buffer[1024];
    va_list args;
    va_start(args, format);

    // Break on alert, if necessary.
    if(format[0] == '!')
    {
        ++format;
#ifdef _MSC_VER
        __debugbreak();
#endif
    }

    vsprintf(print_buffer, format, args);

    va_end(args);
    output_dprintf(print_buffer);
#else
    (void)(format); // Unreferenced parameter.
#endif
}

void set_dprintf(const Output_dprintf output_function) noexcept
{
    if(output_function == nullptr)
    {
        output_dprintf = null_dprintf;
    }
    else
    {
        output_dprintf = output_function;
    }
}

}

