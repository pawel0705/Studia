#include "stdafx.h"
#include "Console.h"
using namespace std;


Console::Console(short width, short height): width(width), height(height)
{
	// Allocate buffer for console
	buffer_background = new CHAR_INFO[width*height];					
	buffer_playground = new CHAR_INFO[width*height];
	
	// Create consolewindows
	window_size = { 0,0, width - 1, height - 1 };
	bufferCoord = { width, height };
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);						// Get console handle
	SetConsoleTitle(L"The animals' playground");					// Set console title
	SetConsoleWindowInfo(hConsole, TRUE, &window_size);				// Set window size
	SetConsoleScreenBufferSize(hConsole, bufferCoord);				// Set screen's buffer size

	// Fill console with green color
																		// Preparing green empty buffer
	for (short y = 0; y < height; ++y)
		for (short x = 0; x < width; ++x)
		{
			GetCharXYInBuffer(buffer_background, x, y)->Char.AsciiChar = (unsigned char)0;
			GetCharXYInBuffer(buffer_background, x, y)->Attributes = BACKGROUND_GREEN;
		}

	CursorHide();
}


Console::~Console()
{
	delete[] buffer_background;
	delete[] buffer_playground;
}


void Console::CopyBackgroundToPlayground()
{
	memcpy(buffer_playground, buffer_background, sizeof(CHAR_INFO) * width * height);
}

void Console::CopyPlaygroundToScreen()
{
	WriteConsoleOutputA(hConsole, buffer_playground, bufferCoord, COORD_00, &window_size);
}

void Console::CursorHide()
{
	CONSOLE_CURSOR_INFO lpCursor{ 20, false };
	SetConsoleCursorInfo(hConsole, &lpCursor);
}

void Console::DrawTextOnBuffer(CHAR_INFO * buffer, short x, short y, string info, WORD color)
{
	const char* text = info.c_str();
	int maxCharsToCopy = width - x - 1;
	int textLength = strlen(text);
	int charsToCopy = textLength > maxCharsToCopy ? maxCharsToCopy : textLength;

	for (int i = 0; i < charsToCopy; i++)
	{
		CHAR_INFO *charptr = GetCharXYInBuffer(buffer, x + i, y);
		charptr->Char.AsciiChar = text[i];
		charptr->Attributes |= color;
	}

}

void Console::DrawRectangleOnBuffer(CHAR_INFO * buffer, short x, short y, short dx, short dy, WORD color)
{

	for (int ix = x; ix <= x + dx; ix++)
		for (int iy = y; iy <= y + dy + 1; iy++)
		{
			if ((ix > 0) && (ix < width) && (iy > 0) && (iy < height))
			{
				CHAR_INFO *charptr = GetCharXYInBuffer(buffer, ix, iy);
				charptr->Attributes = color;
			}
		}
}

CHAR_INFO* Console::GetCharXYInBuffer(CHAR_INFO *buffer, short x, short y)
{
	return &buffer[x + width * y];
}

void Console::DrawTextOnBackground(short x, short y, string info, WORD color)
{
	DrawTextOnBuffer(buffer_background, x, y, info, color);
}

void Console::DrawRectangleOnBackground(short x, short y, short dx, short dy, WORD color)
{
	DrawRectangleOnBuffer(buffer_background, x, y, dx, dy, color);
}

void Console::DrawTextOnPlayground(short x, short y, string info, WORD color)
{
	DrawTextOnBuffer(buffer_playground, x, y, info, color);
}

void Console::DrawRectangleOnPlayground(short x, short y, short dx, short dy, WORD color)
{
	DrawRectangleOnBuffer(buffer_playground, x, y, dx, dy, color);
}


void Console::GotoXY(short x, short y)
{
	SetConsoleCursorPosition(hConsole, COORD{ x, y });
}

bool Console::KeyPressed(int vKey)
{
	SHORT state = GetAsyncKeyState(vKey) && 0x8000;
	return state == 1;
}


#pragma region Accessors
int Console::GetWidth()
{
	return width;
}

int Console::GetHeight()
{
	return height;
}

#pragma endregion 