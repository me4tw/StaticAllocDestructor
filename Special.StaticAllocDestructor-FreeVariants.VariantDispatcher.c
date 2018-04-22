// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief Inliner-visible alternative to function pointers
@ingroup special_staticallocdestructor

Don't say "a simple function pointer would suffice" that is slightly more
error prone, and some c-interpreters and/or transliterators such as certain c-to-javascript
compilers and c-to-java source translators don't like function pointers.

Besides, the inlining optimizer finds function pointers difficult, so get
in the habbit of big switch statements with staticly defined function calls
as a general best practice for performance reasons, even though performance
is not critical here as this probably only happens right at the end when
closing the host program, if at all.
*/
#include "Special.StaticAllocDestructor-FreeVariants.CustomPrototypes.h"
#include "Special.StaticAllocDestructor-Public.h"
void StAlDe_VarianteDispatcher(struct StAlDeNode_tag *nodeToFree)
{
	switch (nodeToFree->freeVariant)
	{
	case STDLIB_FREE:
		stdlib_free(nodeToFree->memoryToFree);
		break;
	case WIN32_HEAP_FREE:
		win32_heap_free(nodeToFree->memoryToFree);
		break;
	}
}
