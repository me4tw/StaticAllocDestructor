// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief secret things
*/
#ifndef	SPECIAL_SEALDE_PRIVATEH
#define	SPECIAL_SEALDE_PRIVATEH

#include "Special.StaticAllocDestructor-Public.h"

/**the start of the list*/
extern struct StAlDeNode_tag *stAlDe_listHeader;

/**the last item in the list*/
extern struct StAlDeNode_tag *stAlDe_latest;

/**Well I think it is clever*/
#ifndef STALDE_CLEVER
#define STALDE_CLEVER 1024
#endif //!STALDE_CLEVER

#if STALDE_CLEVER > 0
/**and i think that this is real clever*/
extern struct StAlDeNode_tag stAlDe_clever[STALDE_CLEVER];
/**this too*/
extern size_t stAlDe_num;
#endif //STALDE_CLEVER > 0

/**
has a big switch statement, used in place of
function pointers inside the linked list nodes
*/
void StAlDe_VarianteDispatcher(struct StAlDeNode_tag *nodeToFree);

#endif //SPECIAL_SEALDE_PRIVATEH
