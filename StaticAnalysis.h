#pragma once

#ifdef _MSC_VER

#include <sal.h>

#else

#define _In_
#define _In_z_
#define _In_reads_(x)
#define _In_reads_opt_(x)
#define _In_reads_to_ptr_(x)
#define _Inout_updates_(x)
#define _Inout_updates_all_(x)
#define _Out_
#define _Out_writes_(x)
#define _Out_writes_all_(x)
#define _Out_writes_to_ptr_(x)
#define _Use_decl_annotations_

#endif


