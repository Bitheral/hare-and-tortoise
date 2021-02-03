#include "console.h"
#include <conio.h>
#include <iostream>

#define ROUND(a) ((int) (a + 0.5))

void Console::clear()
{
	//Description: Clears the screen
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	//Move the cursor back to the default value
	SetConsoleCursorPosition(hConsole, coordScreen);
}

COORD Console::getTextBufferSize(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	return csbi.dwMaximumWindowSize;
}

void Console::setTextBufferSize(short y, short x)
{
	COORD largest = GetLargestConsoleWindowSize(hConsole);

	if (y >= largest.Y)
		y = largest.Y - 1;
	if (x >= largest.X)
		x = largest.X - 1;
		
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(hConsole, &bufferInfo))
		MessageBox(console, "Unable to retrieve screen buffer info.", "Error", MB_OK | MB_ICONERROR);

	SMALL_RECT& winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info =
		{
			0,
			0,
			x < windowSize.X ? x - 1 : windowSize.X - 1,
			y < windowSize.Y ? y - 1 : windowSize.Y - 1
		};

		if (!SetConsoleWindowInfo(hConsole, TRUE, &info))
			MessageBox(console, "Unable to resize window before resizing buffer.", "Error", MB_OK | MB_ICONERROR);
	}

	COORD size = { x, y };
	if (!SetConsoleScreenBufferSize(hConsole, size))
		MessageBox(console, "Unable to resize screen buffer.", "Error", MB_OK | MB_ICONERROR);


	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &info))
		MessageBox(console, "Unable to resize window after resizing buffer.", "Error", MB_OK | MB_ICONERROR);
}

void Console::setCursorPosition(short y, short x)
{
	// Precondition: two non-negative integer parameters for the x and y are provided
	// Description: Moves the cursor to x, y in console window, i.e. x=left\right y=top\bottom
	// Example: gotoXY(10, 10) moves the cursor to those coordinates
	//			gotoXY(0, 10) moves the cursor to those coordinates
	//			gotoXY(-1, 0), gotoXY(0, -1) and gotoXY(-1, -1) throws an exception
	if (x<0 || y<0)
	{
		//setCursorPosition(0, 0);
		std::string message = std::string("Coordinates cannot be less than zero. Attempted: (") + std::to_string(x) + ", " + std::to_string(y) + ")";
		MessageBox(console, message.c_str(), "Error", MB_OK | MB_ICONERROR);
	}
	else
	{
		COORD point = { x, y };
		SetConsoleCursorPosition(hConsole, point);
	}
}

void Console::setCursorPosition(COORD point)
{
	Console::setCursorPosition(point.X, point.Y);
}

void Console::getCursorPosition(short &y, short &x)
{
	COORD point = Console::getCursorPosition();
	x = point.X;
	y = point.Y;
}

COORD Console::getCursorPosition(void)
{
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	GetConsoleScreenBufferInfo(hConsole, &SBInfo);

	return SBInfo.dwCursorPosition;
}

void Console::setColour(COLOUR foreground, COLOUR background)
{
	int colour = background * 16 + foreground;
	SetConsoleTextAttribute(hConsole, colour);
}

void Console::setWindowTitle(std::string title)
{
	SetConsoleTitle(title.c_str());
}

void Console::setWindowSize(size_t height, size_t width)
{
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Console::setWindowPosition(size_t top, size_t left)
{
	SetWindowPos(console, 0, left, top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Console::getWindowPosition(size_t &top, size_t &left)
{
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	top = r.top;
	left = r.left;
}

void Console::getWindowSize(size_t &height, size_t &width)
{
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	width = r.right - r.left;
	height = r.bottom - r.top;
}

char Console::pause(std::string msg)
{
	std::cout << msg;
	char in = _getch();
	std::cout << std::endl;
	return in;
}

HANDLE Console::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HWND Console::console = GetConsoleWindow();
