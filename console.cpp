#include "console.h"

// Ctor
Console::Console()
{
	SetWindowSizeMax();
}

// base utility for output
void Console::output(const string outputVal)
{
	cout << outputVal;
}

// does something ?
void Console::SetWindowSizeMax()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);

	SMALL_RECT windowMaxSize = { 0, 0, info.dwMaximumWindowSize.X - 1, info.dwMaximumWindowSize.Y - 1 };

	SetConsoleWindowInfo(hConsole, TRUE, &windowMaxSize);
}

string Console::toString(const int intVal)
{
	stringstream ss;  // Create stringstream
	ss << intVal;	  // add value of intVal to stringstream

	return ss.str();  // return the contents as a string stream
}

string Console::toString(const bool boolVal)
{
	if (boolVal == true)
		return "true";
	else
		return "false";
}
