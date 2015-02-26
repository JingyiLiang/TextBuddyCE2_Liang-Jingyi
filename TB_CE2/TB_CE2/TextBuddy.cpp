#include "TextBuddy.h"


TextBuddy::TextBuddy(void){}

TextBuddy::TextBuddy(int num){
    _lineNumber = num;
    return;
}

void TextBuddy::addLine(string content){
    _lineList.push_back(content);
    _lineNumber++;
    _lineNumber = _lineNumber + 1;
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
    _lineNumber = 0;
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

int TextBuddy::getLineNum(){
    return _lineNumber;
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

TextBuddy::~TextBuddy(void){}

