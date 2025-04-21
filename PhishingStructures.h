#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <string>
#include <vector>

//structure for the email fields.
struct Email {
    std::string from;
    std::string to;
    std::string subject;
    std::string body;
    std::string signature;
};

//structure for the fields the user selected. 
struct userSelection {
    std::string difficulty;
    std::string from;
    std::string to;
    std::string subject;
    std::string body;
    std::string signature;
};

//structure for the red flag options list.
struct redFlagOptions {
    std::vector<std::string> from;
    std::vector<std::string> to;
    std::vector<std::string> subject;
    std::vector<std::string > body;
    std::vector<std::string> signature;
};

//structure for the red flag options the use selected.
struct userRedFlagSelection {
    std::string from;
    std::string fromReason;
    std::string to;
    std::string toReason;
    std::string subject;
    std::string subjectReason;
    std::string body;
    std::string bodyReason;
    std::string signature;
    std::string signatureReason;
};

//structure for the correct answers.
struct redFlagAnswers {
    std::string from;
    std::string fromAnswer;
    std::string fromDescription;
    std::string to;
    std::string toAnswer;
    std::string toDescription;
    std::string subject;
    std::string subjectAnswer;
    std::string subjectDescription;
    std::string body;
    std::string bodyAnswer;
    std::string bodyDescription;
    std::string signature;
    std::string signatureAnswer;
    std::string signatureDescription;
};

#endif
