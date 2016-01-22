#include "PreCompile.h"
#include "CheckException.h"     // Pick up forward declarations to ensure correctness.
#include "Tracing.h"

namespace PortableRuntime
{

Exception::Exception(const std::string& message)
{
    // TODO: handle bad_alloc
    // TODO: consider std::forward for message?
    m_what = std::make_shared<std::string>(message);
}

const char* Exception::what() const noexcept
{
    return m_what->c_str();
}

namespace Detail
{

// TODO: Add logging in catch statements to pair with the throws?  i.e. "Recovered exception, etc."
_Use_decl_annotations_
void throw_exception(const std::string& message, const char* file_name, int line)
{
    const auto exception_string = std::string(file_name) + '(' + std::to_string(line) + "): " + message;
    dprintf(('!' + exception_string + '\n').c_str());
    throw Exception(exception_string.c_str());
}

}

}

