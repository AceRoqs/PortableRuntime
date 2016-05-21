#include "PreCompile.h"
#include "CheckException.h"     // Pick up forward declarations to ensure correctness.
#include "Tracing.h"

namespace PortableRuntime
{

// TODO: Add logging in catch statements to pair with the throws?  i.e. "Recovered exception, etc."

_Use_decl_annotations_
Exception::Exception(const char* file_name, int line) noexcept : m_file_name(file_name), m_line(line)
{
}

_Use_decl_annotations_
Exception::Exception(const std::string& message, const char* file_name, int line) noexcept : Exception(file_name, line)
{
    try
    {
        dprintf("!%s(%d): %s\n", file_name, line, message.c_str());

        // TODO: consider std::forward for message?
        // Just save off the message now, but do the full formatting in what(), to allow exception unwind to free up some resources.
        m_what = std::make_shared<std::string>(message);
    }
    catch(const std::bad_alloc& ex)
    {
        (void)ex;       // Unreferenced parameter.

        dprintf("!Failed creation of exception object.\n");
    }
}

const char* Exception::what() const noexcept
{
    const char* what = "Allocation failed while handling another exception.";

    try
    {
        if(m_what)
        {
            if(m_formatted)
            {
                what = m_what->c_str();
            }
            else
            {
                auto exception_string = std::string(m_file_name) + '(' + std::to_string(m_line) + "): " + *m_what;
                std::swap(exception_string, *m_what);
                m_formatted = true;
            }
        }
    }
    catch(const std::bad_alloc& ex)
    {
        (void)ex;       // Unreferenced parameter.

        // There isn't enough free memory to format the string, so just return what is available.
        if(m_what)
        {
            what = m_what->c_str();
        }
    }

    return what;
}

Error::Error(const std::string& message, _In_z_ const char* file_name, int line) noexcept : Exception(message, file_name, line)
{
    m_formatted = true;
}

}

