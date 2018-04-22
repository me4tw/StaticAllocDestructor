// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief erase all linked list nodes
*/
#include "Special.StaticAllocDestructor-Private.h"
#include <stdlib.h>

static void StAlDe_EraseAllx(int callDestructors);
void StAlDe_EraseListButDontCallDestructors(void)
{
	StAlDe_EraseAllx(0);
}
void StAlDe_EraseAll(void)
{
	StAlDe_EraseAllx(1);
}

struct StAlDeNode_tag *stAlDe_listHeader = NULL;
struct StAlDeNode_tag *stAlDe_latest = NULL;

#if STALDE_CLEVER > 0
struct StAlDeNode_tag stAlDe_clever[STALDE_CLEVER];
size_t stAlDe_num = 0;
#endif
static void StAlDe_EraseAllx(int callDestructors)
{
#if STALDE_CLEVER > 0
	size_t i = 0;
#endif

	//current/next
	struct StAlDeNode_tag *n = stAlDe_listHeader;
	//prev, for freeing
	struct StAlDeNode_tag *p = NULL;
	//read the name for why another variable for this
	struct StAlDeNode_tag *minimiseConditional = NULL;

	for (; n != NULL; n = n->next
#if STALDE_CLEVER > 0
		, ++i, stAlDe_num=stAlDe_num>0?stAlDe_num-1:0//probably not needed and just a --stAlDe_num would suffice
#endif
		)
	{
		//i'm not sure if it is better to skip ones with empty memory-to-free, 
		//or permit NULL being useful for custom desctructor like one that not
		//needing memory just doing a dedicated atexit type thing, without
		//using the atexit() system
		if(callDestructors)
			StAlDe_VarianteDispatcher(n);
		if (p != NULL
#if STALDE_CLEVER > 0
			//yes, > not >=
			&& i > STALDE_CLEVER
#endif
			)
		{
			//now that p is not being used to get the next pointer anymore, free it
			free(p);
			p = NULL;
			//thats right for getting the last one at the end of the loop
			//it is best not to reuse loop-control vars
			//and we dont want more clever > 0 than needed due to clarity
			minimiseConditional = n;
		}
	}

	//this will only get set to a non-null
	//value if we are already beyond the clever amount
	if (minimiseConditional)
		free(minimiseConditional);

	//the list is now empty
	stAlDe_listHeader = NULL;
	stAlDe_latest = NULL;
}
