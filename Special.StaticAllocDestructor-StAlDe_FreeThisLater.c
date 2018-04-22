// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief add new node
*/
#include "Special.StaticAllocDestructor-Private.h"
#include <stdlib.h>
void StAlDe_FreeThisLater(void*item, const char *optFi, const char *optFu, long optLi, size_t optSz)
{
	StAlDe_FreeThisLaterEx(STDLIB_FREE, item, optFi, optFu, optLi, optSz);
}
void StAlDe_FreeThisLaterEx(enum StAlDeFreeVariant freeVariant, void*item, const char *optFi, const char *optFu, long optLi, size_t optSz)
{
	struct StAlDeNode_tag *newNode = NULL;

	if (!stAlDe_latest)
		stAlDe_latest = stAlDe_listHeader;
#if STALDE_CLEVER > 0
	if (stAlDe_num < STALDE_CLEVER)
	{
		stAlDe_clever[stAlDe_num].freeVariant = freeVariant;
		stAlDe_clever[stAlDe_num].memoryToFree = item;
		stAlDe_clever[stAlDe_num].next = NULL;
		stAlDe_clever[stAlDe_num].miscInfo.major_context = optFi;
		stAlDe_clever[stAlDe_num].miscInfo.minor_context = optFu;
		stAlDe_clever[stAlDe_num].miscInfo.other_context = optLi;
		stAlDe_clever[stAlDe_num].miscInfo.opt_sizeOfMemory = optSz;
		if(stAlDe_latest)
			stAlDe_latest->next = &stAlDe_clever[stAlDe_num];
		if(!stAlDe_listHeader)
			stAlDe_listHeader = &stAlDe_clever[stAlDe_num];
		stAlDe_latest = &stAlDe_clever[stAlDe_num];
		++stAlDe_num;
		return;
	}
	//if this is being used clever mode enabled, this not truly needed
	//as once over the threshold that is it, but if the var exists,
	//lets keep it accurate otherwise it would go negative when freeing, maybe
	++stAlDe_num;
#endif

	//in case custom fields are added later
	newNode = calloc(1, sizeof(struct StAlDeNode_tag));
	if (stAlDe_latest)
		stAlDe_latest->next = newNode;
	if (!stAlDe_listHeader)
		stAlDe_listHeader = newNode;
	newNode->freeVariant = freeVariant;
	newNode->memoryToFree = item;
	newNode->miscInfo.major_context = optFi;
	newNode->miscInfo.minor_context = optFu;
	newNode->miscInfo.opt_sizeOfMemory = optSz;
	newNode->miscInfo.other_context = optLi;
	newNode->next = NULL;
	stAlDe_latest = newNode;
	return;
}


struct StAlDeNode_tag * StAlDe_First(void)
{
	return stAlDe_listHeader;//doesnt need its own source file
}
