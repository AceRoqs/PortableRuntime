#include "PreCompile.h"
#include "CheckException.h"     // Pick up forward declarations to ensure correctness.
#include "Tracing.h"

namespace PortableRuntime
{

namespace Detail
{

using namespace std;

// TODO: Add logging in catch statements to pair with the throws?  i.e. "Recovered exception, etc."
void throw_exception(const string& message, _In_z_ const char* file_name, int line)
{
    const auto exception_string = string(file_name) + '(' + to_string(line) + "): " + message;
    dprintf(('!' + exception_string + '\n').c_str());
    throw exception(exception_string.c_str());
}

}

}

