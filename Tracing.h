#pragma once

namespace PortableRuntime
{

typedef void(*Output_dprintf)(_In_z_ const char* format, va_list args) /* noexcept */;

void dprintf(_In_z_ const char* format, ...) noexcept;

// TODO: Make this a class, which can restore the previous dprintf on scope exit?
void set_dprintf(const Output_dprintf output_function) noexcept;
std::string dprintf_string_from_varargs(_In_z_ const char* format, va_list args) noexcept;

}

