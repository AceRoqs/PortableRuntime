#include "PreCompile.h"
#include "Tracing.h"        // Pick up forward declarations to ensure correctness.

namespace PortableRuntime
{

static void null_dprintf(_In_z_ const char* format, va_list args) noexcept
{
    (void)format;   // Unreferenced parameters.
    (void)args;
}

static Output_dprintf output_dprintf = null_dprintf;

_Use_decl_annotations_
void dprintf(const char* format, ...) noexcept
{
    va_list args;
    va_start(args, format);

    output_dprintf(format, args);

    va_end(args);
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

_Use_decl_annotations_
std::string dprintf_string_from_varargs(const char* format, va_list args) noexcept
{
    char print_buffer[1024];
    vsprintf_s(print_buffer, format, args);

    return print_buffer;
}

}

