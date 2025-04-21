#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include "PhishingStructures.h"
#include <windows.h>

//declaration for the function which gives an error message if 
// a number is not a valid selection.
void numberInvalidMessage();

//declaration for the function which will give a delay when loading
// the sample email message in the browser.
void delay();

//declaration for the function which will clear the screen.
void clearScreen();

//declaration for the function which prompts the user to press enter
// to continue.
void enterToContinue();

//declaration for the function which will display the message to the
// user to select from the red flag options.
void reasonMessage();

//declaration for the function which will validate if a number selection
// is valid.
int numberValidator(std::string number, int min, int max);

//declaration for the function which will display the bad count message.
void badCountMessage(int count);

//declaration for the function to indent the descriptions.
void indentDescription(const std::string text);
	
#endif