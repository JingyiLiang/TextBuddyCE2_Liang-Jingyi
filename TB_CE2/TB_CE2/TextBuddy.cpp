#include "TextBuddy.h"

using namespace std;


const string MESSAGE_WELCOME = "Wellcome to TextBuddy. %s is ready for use";
const string MESSAGE_TERMINATION = "Enter any key to exit:";
const string WARNING_INVALID_COMMAND_ENTERED = "Invalid command: %s";
const string WARNING_COMMAND_LINE_PARAMETER_INPUT_ERROR = "ERROR: Usage: TextBuddy.exe filename.txt";
const string MESSAGE_ADDED = "added to %s: \"%s\"";
const string MESSAGE_DELETED ="deleted from %s: \"%s\"";
const string MESSAGE_EMPTY = "%s is empty";
const string MESSAGE_CLEARED_ALL = "all content deleted from %s";
const string MESSAGE_EXIT = "exit";
const string ERROR_UNRECOGNISED_COMMAND_TYPE = "ERROR: Unrecognised command type";
const string PROMPT_COMMAND =  "command: ";

char buffer[300] = "";

int main(int argc, char* argv[]){
	//command line parameter usage
	string filename;
	TextBuddy tb;

	tb.checkCLI(argc);
	filename = argv[1];
	
	tb.run(filename);
	return 0;
}

void TextBuddy::run(string filename){

	//show welcome message
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(),filename.c_str());
	showToUser(buffer);

	//always loop untill user enter "exit" command
	while(true){
		cout << PROMPT_COMMAND;

		string userCommand;
		getline(cin,userCommand);
		string feedback = executeCommand(filename, userCommand);
		showToUser(feedback);
	}
}

void TextBuddy::checkCLI(int argc){
	if(argc != 2){
		showToUser(WARNING_COMMAND_LINE_PARAMETER_INPUT_ERROR);
		showToUser(MESSAGE_TERMINATION);
		getchar();
		exit(0);
	}
}

string TextBuddy::executeCommand(string filename, string userCommand){
	CommandType command;
	string content;
	string deletedLine;

	command = determineCommandType(getFirstWord(userCommand));
	content = removeFirstWord(userCommand);

	switch(command){
	case Add:
		addLine(content);
		sprintf_s(buffer, MESSAGE_ADDED.c_str(), filename.c_str(),content.c_str());
		return buffer;
	case Display:
		if(_lineList.begin() == _lineList.end()){
			sprintf_s(buffer, MESSAGE_EMPTY.c_str(), filename.c_str());
			return buffer;
		}
		else{
			displayAll();
			return "";
		}
	case Delete:
		deletedLine = deleteLine(content);
		sprintf_s(buffer, MESSAGE_DELETED.c_str(), filename.c_str(), deletedLine.c_str());
		return buffer;
	case Clear:
		clearAll();
		sprintf_s(buffer, MESSAGE_CLEARED_ALL.c_str(),filename.c_str());
		return buffer;
	case Exit:
		writeToFile(filename);
		sprintf_s(buffer, MESSAGE_EXIT.c_str());
		showToUser(buffer);
		exit(0);
	case Invalid:
		sprintf_s(buffer, WARNING_INVALID_COMMAND_ENTERED.c_str(), userCommand.c_str());
		return buffer;
	default:
		showToUser(ERROR_UNRECOGNISED_COMMAND_TYPE);
		showToUser(MESSAGE_TERMINATION); 
		getchar(); 
		exit(0); 
	}
}

void TextBuddy:: writeToFile(string filename){
	ofstream ofs;
	string content;
	content = allToString();
	
	ofs.open(filename);
	ofs << content << endl;
	ofs.close();

	return;
}

string TextBuddy::removeFirstWord(string userCommand){
	return userCommand.substr(userCommand.find_first_of(" ")+1);
}

string TextBuddy::getFirstWord(string userCommand){
	return userCommand.substr(0, userCommand.find(' '));
	//(?)from microsoft VS online resource forum
}

TextBuddy::CommandType TextBuddy::determineCommandType(string firstWord){
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

void TextBuddy::showToUser(string content){
	cout << content << endl;
}
void TextBuddy::addLine(string content){
    _lineList.push_back(content);
    return;
}

string TextBuddy::deleteLine(string lineNum){
    int i = stoi(lineNum);
    string deletedline;
    list<string>::iterator it;

    it = _lineList.begin();
    advance(it, i-1);
    deletedline = *it;
    _lineList.erase(it);
    return deletedline;
}

void TextBuddy::clearAll(){
    _lineList.clear();
    return;
}

void TextBuddy::displayAll(){

    list<string>::iterator it;
    int n = 1;
    for(it = _lineList.begin(); it != _lineList.end(); it++){
        cout << n << "." << *it << endl;
        n++;
    }
    return;
}

string TextBuddy::allToString(){
    ostringstream oss;
    list<string>:: iterator it;
    int n = 1;

    for(it = _lineList.begin(); it != _lineList.end(); it++){
        oss << n << "." << *it << endl;
        n++;
    }

    return oss.str();
}


