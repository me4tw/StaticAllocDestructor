// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief instead of atexit(), use this for the static allocation desctructor system
@defgroup special_staticallocdestructor Special Allocation Destructor
Okay, so we need a special thing to handle the case where code
has static data allocated at runtime (due to being very large size)
and that is theoritically a kind of memory leak because it never
gets freed, so it makes valgrind memleak detection have many false
positives and basically if this whole program ever got wrapped in
some other process it would be leak issue, maybe also for the case
where this program is compiled to .dll and the host .exe unloads and
reloads the program while maintaining the state pointer for things
like dynamic reload of newly compiled code without interupting
program execution type of trick, then static variables will mem
leak every time if you think about it.

Anyway this provides an interface to register a destructor and
just remember to call all of them as appropriate. Just trust me this
is a good idea. You might not want to use atexit().

Normally you will add items to free with.
And free them with StAlDe_EraseAll().
*/

#ifndef	SPECIAL_STATICALLOCDESTRUCTOR_PUBLICH
#define	SPECIAL_STATICALLOCDESTRUCTOR_PUBLICH

#include "Special.StaticAllocDestructor-FreeVariants.Enum.h"
#include <stddef.h>
/**make it all tidier*/
struct StAlDeMiscInfo {
	const char *major_context;/**< for example __FILE__*/
	const char *minor_context;/**< for example functionName();*/
	long other_context;/**< for example __LINE__*/
	size_t opt_sizeOfMemory;
};
/**the main struct at each node of the linked list*/
struct StAlDeNode_tag
{
	struct StAlDeMiscInfo miscInfo; /**<good for display or debug purposes*/
	void *memoryToFree; /**<the main gist of it all, or the meat of it rather I should say*/
	enum StAlDeFreeVariant freeVariant; /**<we don't want function pointers if it can be helped, so you can use freeVariant to put a custom destructor in, and then memoryToFree becomes your userdata pointer*/
	struct StAlDeNode_tag *next;/**<handle to the next node in the list, the final node will have a NULL next pointer*/
};
/**gives the first in the list so you can walk and display it or free manually or whatever*/
struct StAlDeNode_tag * StAlDe_First(void);
/**clears the list out*/
void StAlDe_EraseListButDontCallDestructors(void);
/**normally you will use this one*/
void StAlDe_EraseAll(void);
/**and this one normally too for every place that you malloc() something like that*/
void StAlDe_FreeThisLater(void*item, const char *optFi, const char *optFu, long optLi, size_t optSz);
/**
think about it, if malloc() is the underlying allocator,
and you don't have open OS handles or file handles,
you don't need a destructor function,
just add a new node for every single mallocd member.
Items will be freed in the same order added, not that
that should matter. But if you must then you can add a new
free variant to the enum in Special.StaticAllocDestructor-FreeVariants.Enum.h and then
prototype your destructor in Special.StaticAllocDestructor-FreeVariants.CustomPrototypes.h
and add a call to it in the switch statement in Special.StaticAllocDestructor-FreeVariants.VariantDispatcher.c
*/
void StAlDe_FreeThisLaterEx(enum StAlDeFreeVariant freeVariant, void*item, const char *optFi, const char *optFu, long optLi, size_t optSz);
#endif //SPECIAL_STATICALLOCDESTRUCTOR_PUBLICH
