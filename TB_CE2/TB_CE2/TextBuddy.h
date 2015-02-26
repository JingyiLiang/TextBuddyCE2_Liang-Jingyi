#pragma once

#ifndef TEXTBUDDY_H
#define TEXTBUDDY_H

#include <iostream>
#include <string>
#include <sstream>
#include <list>

using namespace std;

class TextBuddy
{
private:
	list<string> _lineList;
	int _lineNumber;

public:
	TextBuddy(void);
	TextBuddy(int);
	void addLine(string);
	string deleteLine(string);
	void clearAll();
	void displayAll();
	int getLineNum();
	string allToString();
	~TextBuddy(void);

};

#endif

