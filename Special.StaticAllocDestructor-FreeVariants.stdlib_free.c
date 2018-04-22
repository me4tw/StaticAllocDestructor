// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief dont laugh
*/
#include <stdlib.h>

void stdlib_free(void*mem)
{
	free(mem);
}
