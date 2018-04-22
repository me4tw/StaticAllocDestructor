// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief an enum to list all the options
@ingroup special_staticallocdestructor
An enum is good because some compilers will warn if the switch doesnt
have a case for each possibilitiy
*/
#ifndef	SPECIAL_STALDE_FREEVARIANTSH
#define	SPECIAL_STALDE_FREEVARIANTSH

/**
might be needed if things are not using malloc()
at the lowest level aka windows api allocated things
*/
enum test {
	STDLIB_FREE = 1,
	WIN32_HEAP_FREE = 2
};

#endif //SPECIAL_STALDE_FREEVARIANTSH
