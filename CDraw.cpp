#include "CDraw.h"
#include <windows.h>
void CDraw::WriteChar(int x, int y, int foreColor, int backcolor)
{
	HANDLE hStout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hStout, &cci);
	COORD pos = { x * 2,y };
	SetConsoleTextAttribute(hStout, foreColor + backcolor * 0x10);
	SetConsoleCursorPosition(hStout, pos);

}

void CDraw::set()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hInput, &mode); //initialize
	mode |= ENABLE_MOUSE_INPUT;
	SetConsoleMode(hInput, mode);
}

bool CDraw::cls()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the cursor */
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in the current buffer */

	/* get the number of character cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten))
		return false;

	/* get the current text attribute */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;

	/* now set the buffer's attributes accordingly */
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
		return false;

	/* put the cursor at (0, 0) */
	if (!SetConsoleCursorPosition(hConsole, coordScreen))
		return false;
}