// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief Include all function prototypes for custom destructors
@ingroup special_staticallocdestructor

Put all destructor prototypes here even if you also have them somewhere else,
and please keep all platform-specific defines out of it, cast the void* to
the required type inside the body of the destructor, which goes elsewhere.
*/

#ifndef	SPECIAL_STATICALLOCDESTRUCTOR_CUSTOMPROTOH
#define	SPECIAL_STATICALLOCDESTRUCTOR_CUSTOMPROTOH
/**wraps stdlib.h free()*/
void stdlib_free(void*);
/**
wraps windows HeapFree() using the heap retrieved via GetProcessHeap()

If you want other ones you can add a new one for each one in a global or
you can abuse the opt_sizeOfMemory as a void* cast, or you can modify
the struct to have an additional void* inside it
*/
void win32_heap_free(void*);
#endif//SPECIAL_STATICALLOCDESTRUCTOR_CUSTOMPROTOH
