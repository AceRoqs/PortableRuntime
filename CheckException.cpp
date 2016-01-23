#include "PreCompile.h"
#include "CheckException.h"     // Pick up forward declarations to ensure correctness.
#include "Tracing.h"

namespace PortableRuntime
{

// TODO: Add logging in catch statements to pair with the throws?  i.e. "Recovered exception, etc."

_Use_decl_annotations_
Exception::Exception(const std::string& message, const char* file_name, int line) : m_file(file_name), m_line(line)
{
    try
    {
        const auto exception_string = std::string(file_name) + '(' + std::to_string(line) + "): " + message;
        dprintf(('!' + exception_string + '\n').c_str());

        // TODO: consider std::forward for message?
        m_what = std::make_shared<std::string>(exception_string);
    }
    catch(const std::bad_alloc& ex)
    {
        (void)(ex);     // Unreferenced parameter.

        dprintf("!Failed creation of exception object.");
    }
}

const char* Exception::what() const noexcept
{
    return m_what ? m_what->c_str() : "Allocation failed while handling another exception.";
}

}

