//Description: The Phishing Awareness program will help the user practice identifying red flags in phishing email messages.  
// The program will ask the user to select from 3 difficulty levels and the user will need to analyze the sample email 
// message before selecting red flags and the reason why the user believes the field is a red flag. 
//Usage: This program is meant to familiarize users with identifying red flags in email messages.

#define NOMINMAX  //so windows.h min max declarations don't conflict
#include <iostream> //for input and output stream
#include "Question.h" //for the Question class
#include "PhishingStructures.h" //for the header file containing the struct declarations
#include "Utils.h" //for the Utils class
#include <windows.h> //for sleep function//
#include <string> //for getline & string functions//
#include <sstream> //for stringstream//
#include <vector> //for vector to hold temporary fields from input text file//
#include <fstream> //ifstream for reading the file of fields//
#include <cassert> //for the test suites to use assert function

using namespace std;

//The function will display the main menu to the user.  The main menu contains the prompts for the user
// to select the level of difficulty.
string displayMenu(){
    int userChoice;
    string input;

    cout << endl;
    cout << "Please select from the difficulty levels: " << endl;
    cout << endl;
    cout << "Enter 1 for Level 1" << endl;
    cout << "Enter 2 for Level 2" << endl;
    cout << "Enter 3 for Level 3" << endl;
    cout << "Enter 0 to exit" << endl;
    cout << endl;

    while (true) {
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> userChoice)|| !ss.eof()) {
            cout << "Invalid selection, please enter a number between 1 and 3 or 0 to finish: ";
            continue;
        }

        switch (userChoice) {
        case 1: return "1"; break;
        case 2: return "2"; break;
        case 3: return "3"; break;
        case 0: exit(0);
        default: cout << "Invalid selection, please enter a number between 1 and 3 or 0 to finish: ";
        }
    }
}

//This function will display to the user the sample email is loading and gives a delay while the file opens.
void loadingEmailMessage() {
    clearScreen();

    cout << endl;
    cout << "Opening the sample email message in your web browser...";
    
    delay();
}

//This function will display to the user what difficulty they selected.  It will also give them instructions they will need
// for the next screen.  The user will need to press Enter to continue.
void difficultySelectionMessage(string difficulty) {
    clearScreen();

    cout << endl;
    cout << "You have selected Level " << difficulty << " difficulty." << endl;
    cout << endl;
    cout << "The sample email will load in your web browser, please read the Context section of the email message and" << endl;
    cout << "review the From, To, Subject, Body & Signature fields." << endl;
    cout << endl;
    cout << "You will then be prompted to select the fields you believe are red flags.  There could be 1 or more red" << endl;
    cout << "flags in the sample email message." << endl;
    cout << endl;
    cout << "A red flag is an indicator something is suspicous or wrong with the field." << endl;

    enterToContinue();
}

//This function is used to display an error message if the program can't open one of the files it depends on.  The files
// are the html email file, fiedls file, answers file, & options file.  The program will exit once enter is pressed.
void fileOpenError(string file) {
    cout << "Could not open the file: " << file << ". The program will now exit." << endl;
    enterToContinue();
    exit(0);
}

//This function is used to get the data from the file containins the email fields.  The file is split in to a vector,
// the the data is saved to a struct which will the way the program accessess the data.
Email* parseEmailFile(const string& difficulty) {
    string emailFile = "input\\Sample" + difficulty + "_Fields.txt";
    const int EMAIL_FILE_SIZE = 10;
    const int EMAIL_FILE_FROM_FIELD1 = 0;
    const int EMAIL_FILE_FROM_FIELD2 = 1;
    const int EMAIL_FILE_TO_FIELD1 = 2;
    const int EMAIL_FILE_TO_FIELD2 = 3;
    const int EMAIL_FILE_SUBJECT_FIELD1 = 4;
    const int EMAIL_FILE_SUBJECT_FIELD2 = 5;
    const int EMAIL_FILE_BODY_FIELD1 = 6;
    const int EMAIL_FILE_BODY_FIELD2 = 7;
    const int EMAIL_FILE_SIGNATURE_FIELD1 = 8;
    const int EMAIL_FILE_SIGNATURE_FIELD2 = 9;

    ifstream file(emailFile);
    if (!file.is_open()) {
        cout << endl;
        cout << endl;
        fileOpenError(emailFile);
    }
    
    string fields;
    getline(file, fields);

    stringstream ss(fields);
    string token;
    vector<string> emailFields;

    while (getline(ss, token, ',')) {
        if (!token.empty() && token[0] == ' ') token.erase(0, 1);
        emailFields.push_back(token);
    }

    Email* email = new Email();
    if (emailFields.size() == EMAIL_FILE_SIZE) {
        email->from = emailFields[EMAIL_FILE_FROM_FIELD1] + emailFields[EMAIL_FILE_FROM_FIELD2];
        email->to = emailFields[EMAIL_FILE_TO_FIELD1] + emailFields[EMAIL_FILE_TO_FIELD2];
        email->subject = emailFields[EMAIL_FILE_SUBJECT_FIELD1] + emailFields[EMAIL_FILE_SUBJECT_FIELD2];
        email->body = emailFields[EMAIL_FILE_BODY_FIELD1] + emailFields[EMAIL_FILE_BODY_FIELD2];
        email->signature = emailFields[EMAIL_FILE_SIGNATURE_FIELD1] + emailFields[EMAIL_FILE_SIGNATURE_FIELD2];
    }

    return email;
}

//This function is used to get the data from the file containing the red flag options.  The options
// are the reasons why a field might be a red flag.  The data is saved to a struct.
redFlagOptions* parseRedFlagOptionsFile(const string& difficulty, Question& question) {
    string inputFile = "input\\Sample" + difficulty + "_RedFlag_Options.txt";

    ifstream file(inputFile);
    if (!file.is_open()) {
        cout << endl;
        fileOpenError(inputFile);
    }

    const int COUNT_MIN = 1;

    redFlagOptions* redflagoptions = new redFlagOptions();
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string category;
        getline(ss, category, ',');

        if (!category.empty() && category[0] == ' ') category.erase(0, 1);

        vector<string> options;
        string option;

        while (getline(ss, option, ',')) {
            if (!option.empty() && option[0] == ' ') option.erase(0, 1);

            if (!option.empty() && option.back() == ' ') {
                option.erase(option.find_last_not_of(" ") + 1);
            }

            if (!option.empty()) {
                options.push_back(option);
            }
        }

        if (category == "Sender") {
            redflagoptions->from = options;
        }
        else if (category == "Recipient") {
            redflagoptions->to = options;
        }
        else if (category == "Subject") {
            redflagoptions->subject = options;
        }
        else if (category == "Body") {
            redflagoptions->body = options;
        }
        else if (category == "Signature") {
            redflagoptions->signature = options;
        }
    }
    question.setRedFlagOptionsCountMin(COUNT_MIN);

    return redflagoptions;
}

//This function will check if the html sample email is accessible and if it is, it will be opened
// in the users web browser. If the file is not found the program will exit.
void openSampleEmail(string difficulty) {
    string file;
    
    file = "input\\Sample" + difficulty + ".html";
    
    difficultySelectionMessage(difficulty);
    

    ifstream infile(file);
    if (!infile) {
        fileOpenError(file);
    }
    infile.close();
    loadingEmailMessage();

    system(("start " + file).c_str());
}

//This function uses the Question class and the displayFieldsPrompt member function to display the
// user with the available fields they can select.
void userFieldsPrompt(const Email& emailFields) {

    Question question;

    question.displayFieldsPrompt(emailFields);
}

//This function will receive choice made by the user when selecting which fields are red flags.
// The data is saved to the appropriate selection data members by grabbing the data from the
// appropriate email data member.  If the user selects a number outside of the range they
// will receive an error message.
void userFieldsSelection(Email* email, const string& difficulty, userSelection* selection) {
    selection->difficulty = difficulty;

    int userChoice;
    string input;

    while (true) {
        cout << endl;
        cout << "Selection: ";
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> userChoice) || !ss.eof()) {
            cout << "Invalid selection, please enter a number between 1 and 5 or press 0 when you are done: ";
            continue;
        }

        switch (userChoice) {
            case 1: selection->from = email->from;
                cout << endl;
                cout << "You selected the field: " << selection->from << endl;
                break;
            case 2: selection->to = email->to;
                cout << endl;
                cout << "You selected the field: " << selection->to << endl;
                break;
            case 3: selection->subject = email->subject;
                cout << endl;
                cout << "You selected the field: " << selection->subject << endl;
                break;
            case 4: selection->body = email->body;
                cout << endl;
                cout << "You selected the field: " << selection->body << endl;
                break;
            case 5: selection->signature = email->signature;
                cout << endl;
                cout << "You selected the Signature field: " << email->signature << endl;
                break;
            case 0: return;
            default: 
                cout << endl;
                cout << "Invalid selection, please enter a number between 1 and 5 or press 0 when you are done: ";
        }
    }
}

//This function calls the Question class displayUserSelections member function, to display the options the user
// fields the user selected as red flags.
void userSelectionDisplay(const userSelection& selection) {

    Question question;

    question.displayUserSelections(selection);

    return;
}

//This function calls the Question class displayRedFlagOptions member function, to display a list of possible red
// flag reasons.  The user will need to select 1 of the options.  It will display the available options depending
// on what field the user selected as a red flag.
void userRedFlagReasonsPrompt(const userSelection& selection, const redFlagOptions& redflagoptions, userRedFlagSelection& userReason) {

    reasonQuestion question;
    question.displayRedFlagOptions(selection, redflagoptions, userReason);
}

//This function will grab the answers from the answer file, and saved them to a structure.  There are two
// separate strucutre data members which each answer is saved to.  One data member will have the field
// and reason answer together, while the other data member will only have the reason.
redFlagAnswers parseRedFlagAnswerFile(const string& difficulty) {
    string inputFile = "input\\Sample" + difficulty + "_RedFlag_Answers.txt";

    ifstream file(inputFile);
    if (!file.is_open()) {
        fileOpenError(inputFile);
    }

    redFlagAnswers redflaganswers;
    string line;

    while (getline(file, line)) {
        istringstream ss(line);
        string category, answer, description;
        getline(ss, category, ',');
        getline(ss, answer, ',');
        getline(ss, description);

        if (!category.empty() && category[0] == ' ') category.erase(0, 1);
        if (!answer.empty() && answer[0] == ' ') answer.erase(0, 1);
        if (!description.empty() && description[0] == ' ') description.erase(0, 1);

        string combined = category + ": " + answer;

        if (category == "Sender") {
            redflaganswers.fromAnswer = answer;
            redflaganswers.from = combined;
            redflaganswers.fromDescription = description;
        }
        else if (category == "Recipient") {
            redflaganswers.toAnswer = answer;
            redflaganswers.to = combined;
            redflaganswers.toDescription = description;
        }
        else if (category == "Subject") {
            redflaganswers.subjectAnswer = answer;
            redflaganswers.subject = combined;
            redflaganswers.subjectDescription = description;
        }
        else if (category == "Body") {
            redflaganswers.bodyAnswer = answer;
            redflaganswers.body = combined;
            redflaganswers.bodyDescription = description;
        }
        else if (category == "Signature") {
            redflaganswers.signatureAnswer = answer;
            redflaganswers.signature = combined;
            redflaganswers.signatureDescription = description;
        }
    }
    return redflaganswers;
}

//This function will compare the selection made by the user to the correct answers.  The structures used
// as passed to the function for the comparison.  The user will be displayed if their selection(s) were
// correct or incorrect.  The function also adds the number of correct selection and returns the value.
int compareUserSelectionsToAnswers(userRedFlagSelection& selection, const redFlagAnswers* correct, Question& question) {
    int correctCount = 0;
    int badCount = 0;

    cout << "You selected:" << endl;
    cout << endl;

    if (!selection.fromReason.empty()) {
        cout << "- " << selection.fromReason << endl;
        if (selection.fromReason == correct->fromAnswer) {
            correctCount++;
        }
        else {
            badCount++;
        }
    }

    if (!selection.toReason.empty()) {
        cout << "- " << selection.toReason << endl;
        if (selection.toReason == correct->toAnswer) {
            correctCount++;
        }
        else {
            badCount++;
        }
    }

    if (!selection.subjectReason.empty()) {
        cout << "- " << selection.subjectReason << endl;
        if (selection.subjectReason == correct->subjectAnswer) {
            correctCount++;
        }
        else {
            badCount++;
        }
    }

    if (!selection.bodyReason.empty()) {
        cout << "- " << selection.bodyReason << endl;
        if (selection.bodyReason == correct->bodyAnswer) {
            correctCount++;
        }
        else {
            badCount++;
        }
    }

    if (!selection.signatureReason.empty()) {
        cout << "- " << selection.signatureReason << endl;
        if (selection.signatureReason == correct->signatureAnswer) {
            correctCount++;
        }
        else {
            badCount++;
        } 
    }
    question.setIncorrectCount(badCount);

    enterToContinue();
    return correctCount;
}

//This function will display a congratulations message if the user correctly identified the red flag field(s) and the reason(s).  If the user
// selected a lower difficulty, they will receive a message to consider trying a higher difficulty.  If the user did not correctly identify
// all of the red flags and reasons, they will be prompted to either display the correct answer(s) or try again.
void displayAnswersPrompt(const redFlagAnswers* redflaganswers, const Email* email, int totalAnswers, int correctCount, const string difficulty, const int badselections) {
    string input;
    int userChoice;

    Question question;

    if (totalAnswers == correctCount && badselections == 0) {
        clearScreen();
        cout << "Congratulations!!!  You identified all of the red flag fields along with correctly selecting the reasons." << endl;
        if (difficulty == "3") {
            cout << endl;
            cout << "Since you have completed the progam at the highest difficutly, give yourself a round of applause!" << endl;
            enterToContinue();
            return;
        }
        else {
            cout << endl;
            cout << "Since you completed Level " << difficulty << ", try identifying the red flags at a higher level.";
            cout << endl;
            enterToContinue();
            return;
        }
    }
    else {
        cout << "You correctly identified " << correctCount << " out of " << totalAnswers << " possible red flags, and you also made ";
        badCountMessage(badselections);
        cout << "If you want to display the answers press 1 or if you want to try again press 0: ";
    }

    while (true) {
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> userChoice) || !ss.eof()) {
            cout << "Invalid selection, please enter 1 to display the answers or 0 to try again: ";
            continue;
        }

        switch (userChoice) {
        case 1: question.display(redflaganswers, correctCount); return;
        case 0: return;
        default: cout << "Invalid selection, please enter 1 to display the answers or 0 to try again: ";
        }
    }
}

//This funciton is used to delete the dynamic memory allocation used by the structures.
void cleanup(Email* email, redFlagOptions* redflagoptions) {
    delete email;
    delete redflagoptions;
}

int main()
{
    string difficulty;
    int correctCount;
    int totalAnswers;
    int badSelections;

    //This while is used to send the user back to the main menu once they finish a difficutly, unless they select to
    // exit the program.
    while (true) {
        clearScreen();

        cout << "**********************************************************************************************" << endl;
        cout << "************************************* Phishing Awareness *************************************" << endl;
        cout << "**********************************************************************************************" << endl;
        cout << endl;
        cout << "(*) Welcome and thank you for using the program!  The Phishing Simular will display sample (*)" << endl;
        cout << "(*) phishing emails to help you better identify red flags in real phishing emails.         (*)" << endl;
        cout << "**********************************************************************************************" << endl;

        //This variable is used to save the difficulty selected by the user.
        difficulty = displayMenu();

        //This will call the function which opens the appropriate email sample, depending on the difficulty selected.
        openSampleEmail(difficulty);

        //Creates an object for the Question class which will be used later.
        reasonQuestion question;

        //Creates an email object which will contain the data from the email file containing the fields.
        Email* email = parseEmailFile(difficulty);

        //Calls the function which will display the fields the user can select from.
        userFieldsPrompt(*email);

        //Creates a selection object for the UserSelection structure.  Will be used to access the data in the structure.
        userSelection selection;
        //Calls the function which will save the users choices when selecting red flag fields.
        userFieldsSelection(email, difficulty, &selection);

        //Calls the function which will display the selection made by the user when selecting the fields.
        userSelectionDisplay(selection);

        //Creates a redflags object for the redFlagOptions structure.  This will be used to access the data.
        redFlagOptions* redflags = parseRedFlagOptionsFile(difficulty, question);

        //Creates a userReason object for the userRedFlagSelection structure.  This will be used to access the data.
        userRedFlagSelection userReason;

        //Calls the function which will display the list of reasons for the user to select.
        userRedFlagReasonsPrompt(selection, *redflags, userReason);

        //Creates a redflaganswers object for the structure.  It will be used to access the data.
        redFlagAnswers redflaganswers = parseRedFlagAnswerFile(difficulty);

        //Calls the compareUserSelectionsToAnswers function in order to determine which options the user selected were
        // correct, and will save the count to the correctCount variable.
        correctCount = compareUserSelectionsToAnswers(userReason, &redflaganswers, question);

        //Calls the question setAnswerCount member function to save the total answers to the totalAnswers data member.
        question.setAnswerCount(&redflaganswers);

        //Calls the getTotalAnswers member function to get the total possible answer count.
        totalAnswers = question.getTotalAnswers();
        badSelections = question.getIncorrectCount();

        //Calls the function which displays the total number of correct answers the user made and the total possible
        // answers.
        displayAnswersPrompt(&redflaganswers, email, totalAnswers, correctCount, difficulty, badSelections);

        cleanup(email, redflags);
    }
    return 0;
}

