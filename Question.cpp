#include <iostream>
#include "question.h"
#include "PhishingStructures.h"
#include "Utils.h"

using namespace std;

//constructor initializes the private data member.
Question::Question() {
    totalAnswers = 0; redFlagOptionsCountMin = 0; incorrectCount = 0;
}

//function will display the correct answers if the user selects to view the answers.
void Question::display(const redFlagAnswers* redflaganswers, const int correctCount)
{
    int count = 0;

    clearScreen();
    cout << endl;
    cout << "The correct Answers are: " << endl;
    cout << endl;

    if (!redflaganswers->from.empty()) {
        cout << "- " << redflaganswers->from << endl;
        indentDescription(redflaganswers->fromDescription);
        cout << endl;
    }
    if (!redflaganswers->to.empty()) {
        cout << "- " << redflaganswers->to << endl;
        indentDescription(redflaganswers->toDescription);
        cout << endl;
    }
    if (!redflaganswers->subject.empty()) {
        cout << "- " << redflaganswers->subject << endl;
        indentDescription(redflaganswers->subjectDescription);
        cout << endl;
    }
    if (!redflaganswers->body.empty()) {
        cout <<  "- " << redflaganswers->body << endl;
        indentDescription(redflaganswers->bodyDescription);
        cout << endl;
    }
    if (!redflaganswers->signature.empty()) {
        cout << "- " << redflaganswers->signature << endl;
        indentDescription(redflaganswers->signatureDescription);
        cout << endl;
    }
    enterToContinue();

    return;
}

//function will count the number of answers and save the value to totalAnswers.
void Question::setAnswerCount(const redFlagAnswers* redflaganswers) {
    int count = 0;

    if (!redflaganswers->fromAnswer.empty()) {
        count++;
    }
    if (!redflaganswers->toAnswer.empty()) {
        count++;
    }
    if (!redflaganswers->subjectAnswer.empty()) {
        count++;
    }
    if (!redflaganswers->bodyAnswer.empty()) {
        count++;
    }
    if (!redflaganswers->signatureAnswer.empty()) {
        count++;
    }
    totalAnswers = count;
}

void Question::setRedFlagOptionsCountMin(int count) {
    redFlagOptionsCountMin = count;
}

void Question::setIncorrectCount(int count) {
    incorrectCount = count;
}

//function will get the value of totalAnswers.
int Question::getTotalAnswers() const {
    return totalAnswers;
}

int Question::getRedFlagOptionsCountMin() const {
    return redFlagOptionsCountMin;
}

int Question::getIncorrectCount() const {
    return incorrectCount;
}

//function will display the list of fields which the user can select as possible red
// flag fields.
void Question::displayFieldsPrompt(const Email& emailFields)
{
    cout << endl;
    cout << endl;
    cout << "Enter the number of the field or fields you believe are red flags: " << endl;
    cout << endl;
    cout << "1. " << emailFields.from << endl;
    cout << "2. " << emailFields.to << endl;
    cout << "3. " << emailFields.subject << endl;
    cout << "4. " << emailFields.body << endl;
    cout << "5. " << emailFields.signature << endl;
    cout << "0. Finish" << endl;
}

//function will display the selection the user made when selecting the fields which
// they believe are red flags.
void Question::displayUserSelections(const userSelection& selection) {
    clearScreen();
    cout << "You have selected the following Fields:" << endl;
    cout << endl;

    int fieldNumber = 1;

    if (!selection.from.empty()) {
        cout << fieldNumber++ << ". " << selection.from << endl;
    }
    if (!selection.to.empty()) {
        cout << fieldNumber++ << ". " << selection.to << endl;
    }
    if (!selection.subject.empty()) {
        cout << fieldNumber++ << ". " << selection.subject << endl;
    }
    if (!selection.body.empty()) {
        cout << fieldNumber++ << ". " << selection.body << endl;
    }
    if (!selection.signature.empty()) {
        cout << fieldNumber++ << ". " << selection.signature << endl;
    }
    return;
}

//construct
reasonQuestion::reasonQuestion(){}

//function will display to the user a list of reasons on why the field(s) they selected could be red flags.
// the user will need to select 1 option from each field they previously selected.  The value for the choice
// they made will be saved to the userSelection structure.
void reasonQuestion::displayRedFlagOptions(const userSelection& selection, const redFlagOptions& redflagoptions, userRedFlagSelection& reasons) {
    int minOptionNum = getRedFlagOptionsCountMin();
    int optionNumber = 1;
    string userChoice;
    int validNumber;
    cout << endl;

    if (!selection.from.empty()) {
        int maxOptionNum = redflagoptions.from.size();
        cout << "For your selection: ";
        cout << selection.from << endl;
        cout << endl;

        for (size_t i = 0; i < redflagoptions.from.size(); ++i) {
            cout << "   " << optionNumber++ << ". " << redflagoptions.from[i] << endl;
        }
        cout << endl;
        reasonMessage();
        getline(cin, userChoice);
        validNumber = numberValidator(userChoice,minOptionNum,maxOptionNum);
        reasons.fromReason = redflagoptions.from[validNumber - 1];
        cout << endl;
    }

    if (!selection.to.empty()) {
        int maxOptionNum = redflagoptions.to.size();
        optionNumber = 1;

        cout << "For your selection: ";
        cout << selection.to << endl;
        cout << endl;

        for (size_t i = 0; i < redflagoptions.to.size(); ++i) {
            cout << "   " << optionNumber++ << ". " << redflagoptions.to[i] << endl;
        }
        cout << endl;
        reasonMessage();
        getline(cin, userChoice);
        validNumber = numberValidator(userChoice, minOptionNum, maxOptionNum);
        reasons.toReason = redflagoptions.to[validNumber - 1];
        cout << endl;
    }

    if (!selection.subject.empty()) {
        int maxOptionNum = redflagoptions.subject.size();
        optionNumber = 1;

        cout << "For your selection: ";
        cout << selection.subject << endl;
        cout << endl;

        for (size_t i = 0; i < redflagoptions.subject.size(); ++i) {
            cout << "   " << optionNumber++ << ". " << redflagoptions.subject[i] << endl;
        }
        cout << endl;
        reasonMessage();
        getline(cin, userChoice);
        validNumber = numberValidator(userChoice, minOptionNum, maxOptionNum);
        reasons.subjectReason = redflagoptions.subject[validNumber - 1];
        cout << endl;
    }

    if (!selection.body.empty()) {
        int maxOptionNum = redflagoptions.body.size();
        optionNumber = 1;

        cout << "For your selection: ";
        cout << selection.body << endl;
        cout << endl;

        for (size_t i = 0; i < redflagoptions.body.size(); ++i) {
            cout << "   " << optionNumber++ << ". " << redflagoptions.body[i] << endl;
        }
        cout << endl;
        reasonMessage();
        getline(cin, userChoice);
        validNumber = numberValidator(userChoice, minOptionNum, maxOptionNum);
        reasons.bodyReason = redflagoptions.body[validNumber - 1];
        cout << endl;
    }

    if (!selection.signature.empty()) {
        int maxOptionNum = redflagoptions.signature.size();
        optionNumber = 1;

        cout << "For your selection: ";
        cout << selection.signature << endl;
        cout << endl;

        for (size_t i = 0; i < redflagoptions.signature.size(); ++i) {
            cout << "   " << optionNumber++ << ". " << redflagoptions.signature[i] << endl;
        }
        cout << endl;
        reasonMessage();
        getline(cin, userChoice);
        validNumber = numberValidator(userChoice, minOptionNum, maxOptionNum);
        reasons.signatureReason = redflagoptions.signature[validNumber - 1];
        cout << endl;
    }
}
