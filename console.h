#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>

using std::stringstream;
using std::cout;
using std::string;

class Console
{
private:
	void SetWindowSizeMax();

public:
	Console();
	void output(const string);
	string toString(const int);
	string toString(const bool);
};