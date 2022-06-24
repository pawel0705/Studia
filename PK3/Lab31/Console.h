#pragma once
#include <windows.h>
#define COORD_00 COORD{ 0, 0 }

class Console
{
private:
	// Win32 console stuff
	short width;
	short height;

	HANDLE hConsole;
	SMALL_RECT window_size;
	COORD bufferCoord;
	CHAR_INFO *buffer_background = nullptr;
	CHAR_INFO *buffer_playground = nullptr;

public:
	Console(short, short);
	~Console();

	// Win32 console stuff
	void CopyBackgroundToPlayground();
	void CopyPlaygroundToScreen();

	void DrawTextOnBuffer(CHAR_INFO *, short, short, const std::string, WORD);
	void DrawRectangleOnBuffer(CHAR_INFO *, short, short, short, short, WORD);
	CHAR_INFO* GetCharXYInBuffer(CHAR_INFO *, short, short);

	void DrawTextOnBackground(short x, short y, const std::string, WORD);
	void DrawRectangleOnBackground(short, short, short, short, WORD);
	void DrawTextOnPlayground(short x, short y, const std::string, WORD);
	void DrawRectangleOnPlayground(short, short, short, short, WORD);

	void CursorHide();
	bool KeyPressed(int vKey);
	void GotoXY(short x, short y);

	// Accesors
	int GetHeight();
	int GetWidth();
};

