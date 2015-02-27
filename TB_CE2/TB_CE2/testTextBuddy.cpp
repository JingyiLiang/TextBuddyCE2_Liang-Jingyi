#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <list>
#include "TextBuddy.h"

using namespace std;

enum CommandType {Add = 0, Display = 1, Delete = 2, Clear =3, Exit = 4, Invalid = 5};

const string MESSAGE_WELCOME = "Wellcome to TextBuddy. %s is ready for use";
const string MESSAGE_TERMINATION = "Enter any key to exit:";
const string WARNING_INVALID_COMMAND_ENTERED = "Invalid command: %s";
const string WARNING_COMMAND_LINE_PARAMETER_INPUT_ERROR = "ERROR: Usage: TextBuddy.exe filename.txt";
const string MESSAGE_ADDED = "added to %s: \"%s\"";
const string MESSAGE_DELETED ="deleted from %s: \"%s\"";
const string MESSAGE_EMPTY = "%s is empty";
const string MESSAGE_CLEARED_ALL = "all content deleted from %s";
const string MESSAGE_EXIT = "exit";
char buffer[300];

CommandType determineCommandType(string firstWord);

string removeFirstWord(string userCommand);
string getFirstWord(string userCommand);
string executeCommand(string filename, string userCommand, TextBuddy tb1);

void showToUser(string content);
void writeToFile(string filename, TextBuddy tb1);

int main (/*int argc, char* argv[]*/){
	//command line parameter usage
	string filename;

	/*if(argc != 2){
		showToUser(WARNING_COMMAND_LINE_PARAMETER_INPUT_ERROR);
		showToUser(MESSAGE_TERMINATION);
		getchar();
		exit(0);
	}*/

	//filename = argv[1];
	cin >> filename;

	//write into buffer first
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(),filename.c_str());
	showToUser(buffer);

	//create a new TextBuddy item
	TextBuddy tb1();

	//always loop untill user enter "exit" command
	while(true){
		cout << "command:"<< endl;
		string userCommand;
		getline(cin,userCommand);
		string feedback = executeCommand(filename, userCommand);
		showToUser(feedback);
	}
}

string executeCommand(string filename, string userCommand, TextBuddy tb1){
	CommandType command;
	string content;
	string deletedLine;

	command = determineCommandType(getFirstWord(userCommand));
	content = removeFirstWord(userCommand);

	switch(command){
	case Add:
		tb1.TextBuddy::addLine(content);
		sprintf_s(buffer, MESSAGE_ADDED.c_str(), filename.c_str(),content.c_str());
		return buffer;
	case Display:
		if(tb1.TextBuddy::getLineNum() == 0){
			sprintf_s(buffer, MESSAGE_EMPTY.c_str(), filename.c_str());
			return buffer;
		}
		else{
			tb1.displayAll();
			return "";
		}
	case Delete:
		deletedLine = tb1.TextBuddy::deleteLine(content);
		sprintf_s(buffer, MESSAGE_DELETED.c_str(), filename.c_str(), deletedLine.c_str());
		return buffer;
	case Clear:
		tb1.TextBuddy::clearAll();
		sprintf_s(buffer, MESSAGE_CLEARED_ALL.c_str(),filename.c_str());
		return buffer;
	case Exit:
		writeToFile(filename, tb1);
		sprintf_s(buffer, MESSAGE_EXIT.c_str());
		showToUser(buffer);
		exit(0);
	case Invalid:
		sprintf_s(buffer, WARNING_INVALID_COMMAND_ENTERED.c_str(), userCommand.c_str());
		return buffer;
	}
}

void writeToFile(string filename, TextBuddy tb1){
	ofstream ofs;
	string content;
	content = tb1.allToString();
	
	ofs.open(filename);
	ofs << content << endl;
	ofs.close();

	return;
}

string removeFirstWord(string userCommand){
	return userCommand.substr(userCommand.find_first_of(" ")+1);
}

string getFirstWord(string userCommand){
	return userCommand.substr(0, userCommand.find(' '));
	//(?)from microsoft VS online resource forum
}

CommandType determineCommandType(string firstWord){
	// allow natural typing variations
	transform(firstWord.begin(), firstWord.end(),firstWord.begin(), ::tolower);
	
	if (firstWord == "add"){
		return CommandType::Add;
	}
	else if (firstWord == "display"){
		return CommandType::Display;
	}
	else if (firstWord == "delete"){
		return CommandType::Delete;
	}
	else if (firstWord == "exit"){
		return CommandType::Exit;
	}
	else if(firstWord == "clear"){
		return CommandType::Clear;
	}
	else return CommandType::Invalid;
}

void showToUser(string content){
	cout << content << endl;
}