#ifndef QUESTION_H
#define QUESTION_H

#include "PhishingStructures.h"

class Question {
public:
    //constructor
    Question();
    
    //function declaration for the function which diplays the fields the user can select from.
    void displayFieldsPrompt(const Email& emailFields);

    //function declaration for the function which displays selections made by the user.
    void displayUserSelections(const userSelection& selection);

    //function declaration for the function which displays the correct answers.
    void display(const redFlagAnswers* redflagsanswer, const int correctCount);

    //function declaration for the function to count the total possible correct answers and
    // saves to the totalAnswers data member.
    void setAnswerCount(const redFlagAnswers* redflaganswers);

    //function declaration for the function which will get the value of the totalAnswers
    // data member.
    int getTotalAnswers() const;

    //sets the mininum count for the red flags.
    void setRedFlagOptionsCountMin(int count);

    //sets the incorrect user selection count.
    void setIncorrectCount(int count);

    //gets the red flag minimum count.
    int getRedFlagOptionsCountMin() const;

    //gets the incorrec count.
    int getIncorrectCount() const;

private:
    int totalAnswers;
    int redFlagOptionsCountMin;
    int incorrectCount;
};

//the reasonQuestion class inherits from the Question class.
class reasonQuestion : public Question {

public:
    //constructor
    reasonQuestion();

    //function declaration for the function which will display the user with a list of reason they will
    // select from.
    void displayRedFlagOptions(const userSelection& selection, const redFlagOptions& redflagoptions, userRedFlagSelection& reasons);

};



#endif