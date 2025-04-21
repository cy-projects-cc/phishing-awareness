# Phishing Awareness Program

This is a C++ console application that helps the user identify the red flags contained in common phishing emails.
The users will be prompted to select a difficulty level and then prompted to identify the suspicious fields (red
flags) and then give a reason why they are suspicious.

The program will evaluate the users selections to the correct answers and provide feedback if they correctly
identified the red flags and reasons.

- Choose from different difficulty levels
- View and analyze phishing email samples
- Identify red flags in email fields
- Select reasons behind the red flag selections
- Receive feedback of how many you correctly selected

## Getting Started

### Prerequisites
- Windows OS (uses 'windows.h')
- A C++ compiler

###Compilation Instructions

1. Open Visual Studio
2. Create a new Console App Project
3. Add the .cpp and .h files to the project
4. Add the input/ folder to the working directory (where the .exe runs).
5. Build and run with the Green Local Windows Debugger button.

## File Structure

- phishingawarenessprogram.cpp - Main program logic
- Question.h / Question.cpp - Handles prompts, answers, and inherited class logic
- Utils.h / Utils.cpp - Utility functions (screen clearing, input validation, etc.)
- PhishingStructure.h - All struct definitions used in the program
- input/ - Contains the input files for the sample emails, email fields, red flag options, and answers

## Input Files

You will want to place the input files in a folder named input which is in the same location as the program is being ran.

Sample1.html
Sample1_Fields.txt
Sample1_RedFlag_Answers.txt
Sample1_RedFlag_Options.txt
Sample2.html
Sample2_Fields.txt
Sample2_RedFlag_Answers.txt
Sample2_RedFlag_Options.txt
Sample3.html
Sample3_Fields.txt
Sample3_RedFlag_Answers.txt
Sample3_RedFlag_Options.txt

### Sample Email File Format

The input file used to display the sample phishing email in in html.  The name starts with Sample and then either 1-3 for the level.

### Email Fields File Format

The Sample*_Fields file is a text document with commas separating the values and each line starts with the field name.  The name
contains a number between 1-3 for the level.

From:<email address>
To:<email address>
Subject:<subject>
Body:<body message>
Signature:<signature>

### Email Red Flags Answer File Format

The Sample*_RedFlag_Options.txt file is a text document with commas separating the values, and each correct answer starts with the field name.  
The name contains a number between 1-3 for the level.

From:<answer>, <description>
To:<answer>, <description>
Subject:<answer>, <description>
Body:<answer>, <description>
Signature:<answer>, <description>

### Email Red Flags Options File Format

The Sample*_RedFlag_Options.txt file is a text document with commas separating the values.  Each line contains the field name at the 
beginning and then the reasons.  The name contains a number between 1-3 for the level.

From:<reason1>, <reason2>, etc.
To:<reason2>, <reason2>, etc.
Subject:<reason1>, <reason2>, etc.
Body:<reason1>, <reason2>, etc.
Signature:<reason1>, <reason2>, etc.

## Usage

1. Compile the program
2. Create the input folder in the same directory the program will run from
3. Save the input files in the input folder
4. Choose a difficulty level.
5. Analyze the displayed email message.
6. Select the fields you believe are red flags.
7. View how many you correctly and incorrectly selected.

## Sample Output

You correctly identified 2 out of 3 possible red flags, and you also made 1 incorrect selection.

If you want to display the answers press 1 or if you want to try again press 0:

## Credits

Created by cy-projects-cc for the final project of COMPSCI-2
