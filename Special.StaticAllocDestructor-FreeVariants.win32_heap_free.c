// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Everywhere.h"
/**
@file
@brief a bit overengineered for what probably no one will use, maybe
*/
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
void win32_heap_free(void*mem)
{
	HANDLE theHeap = INVALID_HANDLE_VALUE;
	BOOL success = FALSE;
	if (!mem)
		return;//undefined behavour to heapfree on null

	theHeap = GetProcessHeap();
	success = HeapFree(theHeap, 0, mem);
	if (!success)
	{
		DWORD error = GetLastError();
		if (GetConsoleWindow() == NULL)//no console window, create one then
		{
			AllocConsole();//we want the user to actually see the message
			if (GetConsoleWindow() != NULL)//and messageboxA will interrupt program execution
			{
				HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
				int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
				FILE* hf_out = _fdopen(hCrt, "w");
				setvbuf(hf_out, NULL, _IONBF, 1);
				*stdout = *hf_out;

				HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
				hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
				FILE* hf_in = _fdopen(hCrt, "r");
				setvbuf(hf_in, NULL, _IONBF, 128);
				*stdin = *hf_in;
			}

			// use the console just like a normal one - printf(), getchar(), ...
		}
		fprintf(stderr, "\nerror occured doing HeapFree(): %u ", error);
		//add some details
		{
			LPSTR messageBuffer = NULL;
			size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

			if (messageBuffer)
			{
				fputs(messageBuffer,stderr);
				//Free the buffer.
				LocalFree(messageBuffer);
			}
		}
		fputc('\n', stderr);
	}
}
