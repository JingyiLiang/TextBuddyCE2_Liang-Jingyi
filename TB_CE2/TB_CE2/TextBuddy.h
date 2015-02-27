#pragma once

#ifndef TEXTBUDDY_H
#define TEXTBUDDY_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <list>
#include "TextBuddy.h"

using namespace std;

class TextBuddy
{
private:
	list<string> _lineList;
	/*const string MESSAGE_WELCOME;
	const string MESSAGE_TERMINATION;
	const string WARNING_INVALID_COMMAND_ENTERED;
	const string WARNING_COMMAND_LINE_PARAMETER_INPUT_ERROR;
	const string MESSAGE_ADDED;
	const string MESSAGE_DELETED;
	const string MESSAGE_EMPTY;
	const string MESSAGE_CLEARED_ALL;
	const string MESSAGE_SORTED_ALL;
	const string MESSAGE_SEARCH_RESULT;
	const string MESSAGE_EXIT;
	const string ERROR_UNRECOGNISED_COMMAND_TYPE;
	const string PROMPT_COMMAND;*/
	char buffer[300];
public:
	TextBuddy();
	void addLine(string);
	string deleteLine(string);
	void clearAll();
	void displayAll();
	string allToString();

	enum CommandType {Add = 0, Display = 1, Delete = 2, Clear =3, Exit = 4, Sort = 5, Search = 6, Invalid = 7};

	CommandType determineCommandType(string firstWord);
	string removeFirstWord(string userCommand);
	string getFirstWord(string userCommand);
	string executeCommand(string filename, string userCommand);
	string searchFile(string content);

	void run(string filename);
	void writeToFile(string filename);
	static void showToUser(string content);
	void sortFile();
    //void checkCLI(int argc);

};

#endif

