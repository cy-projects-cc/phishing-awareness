#define NOMINMAX //for max for buffer clear
#include <iostream>
#include <sstream>
#include "question.h"
#include "PhishingStructures.h"
#include <windows.h> //for delay sleep function

using namespace std;

//function will display the error message if the user enters an invalid number when selecting
// from the red flag options.
string numberInvalidMessage() {
    return "This is not a valid selection, please select a valid number: ";
}

//function which gives a dealy while the sample email is opened in the users browser.
void delay() {
    Sleep(2000);
}

//Used to clear the screen.
void clearScreen() {
    system("cls");
}

//Used to prompt the user to press enter to continue.
void enterToContinue() {
    string tmpStr;

    cout << endl;
    cout << "Press enter to continue." << endl;
    getline(cin, tmpStr);
}

//Used to display the message for the user to seelct from the red flag options.
void reasonMessage() {
    cout << "Please select the correct red flag reason from the listed options: ";
}

void badCountMessage(int count) {

    if (count == 1) {
        cout << count << " incorrect selection." << endl;
        cout << endl;
    }
    else {
        cout << count << " incorrect selections." << endl;
        cout << endl;
    }
}

//function that will validate the number selected is in the correct range.
int numberValidator(string number, int min, int max) {
    int validNumber;

    while (true) {
        stringstream ss(number);
        if (ss >> validNumber && ss.eof()) {
            if (validNumber >= min && validNumber <= max) {
                return validNumber;
            }
        }
        cout << endl;
        cout << numberInvalidMessage();
        getline(cin, number);
    }
}

//function will indent the description when displaying the answers.
void indentDescription(const string text) {
    int indent = 4;
    int width = 80;
    istringstream iss(text);
    string word;
    string line(indent, ' ');

    while (iss >> word) {
        
        if (line.length() + word.length() + 1 > width) {
            cout << line << endl;
            line = string(indent, ' ') + word;
        }
        else {
            if (line.length() > indent)
                line += " ";
            line += word;
        }
    }

    if (!line.empty()) {
        cout << line << std::endl;
    }
}
