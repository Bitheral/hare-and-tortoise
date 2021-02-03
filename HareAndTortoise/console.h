#pragma once
#include <string>
#include <windows.h>


/**
\class	Console

\brief	This class is designed to wrap around built in console functions
		Note: it is a windows only implementation and will not work within a Linux based OS

		Functions included are:
		- clear			: Clears the entire console buffer with the space character
		- pause			: Asks the user to enter any character to continue
		- gotoXY		: Moves the cursor to the XY location within the console
		- setTitle		: Sets the title of the console
		- setSize		: Sets the size of the console window (pixels)
		- setPosition	: Sets the position of the console window (pixels)
		- getSize		: Gets the size of the console window (pixels)	
		- getPosition	: Gets the position of the console window (pixels)

*/
class Console
{
private:
	static HANDLE hConsole;
	static HWND console;

public:
	/**
	\brief Built in colours that can be used within a console as their integer representation
	*/
	static enum COLOUR {
				BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, DEFAULT, GRAY, LIGHT_BLUE,
				LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, WHITE
			};

	
	/** 
	\fn static void gotoXY(short y, short x);
	\brief  
	Precondition: two non-negative integer parameters for the x and y are provided
	Description: Moves the cursor to x, y in console window, i.e. x=left|right y=top|bottom
	Example: setCursorPosition(10, 10) moves the cursor to those coordinates
				setCursorPosition(0, 10) moves the cursor to those coordinates
				setCursorPosition(-1, 0), setCursorPosition(0, -1) and setCursorPosition(-1, -1) throw an exception

	\param	y short indicating the row
	\param	x short indicating the column
		*/
	static void setCursorPosition(short y = 0, short x = 0);

	static void setCursorPosition(COORD);

	static void getCursorPosition(short &y, short &x);

	static COORD getCursorPosition(void);
	

	static COORD getTextBufferSize(void);
	static void setTextBufferSize(short y = SHRT_MAX, short x = SHRT_MAX);
	/** 
	\fn		static void setColour(COLOUR foreground, COLOUR background = Console::BLACK);
	\brief 
	Precondition: an enumerated COLOUR foreground and background type for colour is required from
					BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, DEFAULT, GRAY, LIGHT_BLUE, 
					LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, WHITE
	 Postcondition: text foreground and background colour is changed to one of these 256 possibilities
	 Description: changes the foreground and background text colour within the console window
	 Example: setColour(BLACK, WHITE) changes the foreground text colour to black and the background to white.
	\param foreground The colour of the text
	\param background The colour of the background in the console window
	*/
	static void setColour(COLOUR foreground, COLOUR background = Console::BLACK);

	/**
	\fn		static void setTitle(std::string);
	\brief	Pass in a string to set the title of your console window
	\param	title A string containing the title of the window
	*/
	static void setWindowTitle(std::string title);


	/**
	\fn		static void setSize(size_t height, size_t width);
	\brief	Pass in the height and width for your console window. 
	\param	height	[Passed in pixels]
	\param	width	[Passed in pixels]
	*/
	static void setWindowSize(size_t height, size_t width);

	/**
	\fn		static void getSize(size_t &height, size_t &width);
	\brief	Returns by reference the height and the width of the console
	\param [out] height	[Passed in pixels]
	\param [out] width	[Passed in pixels]
	*/
	static void getWindowSize(size_t &height, size_t &width);
	/**
	\fn		static void setPosition(size_t top, size_t left);
	\brief  Pass in the top and left coordinate that you would like to use for your console window. 
	\param	top		[Passed in pixels]
	\param	left	[Passed in pixels]
	*/
	static void setWindowPosition(size_t top, size_t left);

	/**
	\fn		static void getPosition(size_t &top, size_t &left);
	\brief	Returns by reference the height and the width of the console
	\param [out] top	[Passed in pixels]
	\param [out] left	[Passed in pixels]
	*/
	static void getWindowPosition(size_t &top, size_t &left);


	/**
	\fn		static char pause(std::string msg = "Press any key to continue...");
	\brief	Provides similar functionality to system("pause")
			But this function is better as it does not load in another program.
			Outputs the passed in message ("Press any key to continue..." by default)
			Checks for any key being pressed on the keyboard
			returns the pressed key (just encase you need the value)
	\param msg the message you would like to display to the user for the pause
	\return char representing the character the user pressed on the keyboard
	*/
	static char pause(std::string msg = "Press any key to continue...");

	/**
	\fn		static void clear();
	\brief  Clears the entire console screen buffer with the space character
	*/
	static void clear();	
};
