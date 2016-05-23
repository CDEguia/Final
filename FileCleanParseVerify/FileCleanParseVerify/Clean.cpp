//---------------------------------------------------------------
//          Name		Candelario D. Eguia
//			Name        Jeremy Driesler
//          Course		CMPS-455
//          Project		Final
//          Due date	Mar. 13, 2016
//          Professor	Ray Ahmadnia
//
// This program will:
//       Clean up and copy a text file, Determin if the program is accepted by the Grammar provided, display posible errors, convert to C++ code.
//------------------------------------------------------------------
//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "Functions.h"

using namespace std;

int main() {
	char reservedWords[6][10] = { "program", "var", "begin", "end.", "integer", "write" };
	char special[10] = { '+' , '-' , '*' , '/' ,'=' ,  ';' , '(' , ')' , ',', ':' };
	char w[200];

	fstream inp, outp;				//base file

	inp.open("finalv1.txt", ios::in);	//open the file that includes the strings to check
	outp.open("finalv2.txt", ios::out);

	inp.getline(w, 200);
	while (!inp.eof())				//loop through the lines in the text file
	{
		int i = 0;
		while (w[i] != NULL)		//loops through character in each w
		{
			if (w[i] == '/' && w[i + 1] == '/') {
				i += 2;
				while (w[i] != '/' && w[i + 1] != '/') {
					if (w[i] == NULL) {
						inp.getline(w, 200);
						break;
					}
					i++;
				}
				break; //skips any commented code & gets next w
			}
			else if (w[i] == ' ') {
				//does nothing but get next char by skiping to end of "if" block
			}
			else if (isNumber(w[i])) // Integer check
			{						//single digits only
				outp << w[i] << " ";
				cout << w[i] << " ";
			}
			else if (isLetter(w[i])) {
				int wordLength = wordCheck(w, i, special);
				char word[15];
				for (int n = 0; n < wordLength; ++n) {
					word[n] = w[i + n];
				}
				word[wordLength] = char(0);
				i += wordLength - 1;
				cout << word;
				outp << word;
				if (w[i + 1] != NULL) {
					outp << " ";
					cout << " ";
				}
				else {
					outp << endl;
					cout << endl;
				}
			}
			else {
				if (w[i] == ';') {
					outp << w[i] << endl;
					cout << w[i] << endl;
				}
				else {
					outp << w[i] << " ";
					cout << w[i] << " ";
				}
			}
			i++;
		}
		inp.getline(w, 200);
	}
	//close the file stream
	inp.close();
	outp.close();

	cout << "\nYour file has been cleaned up. \nThe new version is now stored in: finalv2.txt\n";
	std::system("pause");
	cout << "\nVerifing File: finalv2.txt ...\n\n";
	//
	// PART II
	//
	inp.open("finalv2.txt", ios::in);	//open the file that includes the strings to check
	outp.open("finalv3.txt", ios::out);
	STACK stack;

	int langValues[8][2] = { { 8,3 },{ 8,3 },{ 8,1 },{ 9,3 },{ 9,3 },{ 9,1 },{ 10,3 },{ 10,1 } };
	//
	// End Parcing Table section
	//
	//getline(inp, w, '\n');		//Get first w of file
	int lineNumber = 1;
	inp.getline(w, 200);

	while (!inp.eof())				//loops untill End Of File is read
	{
		int posInfo = 0, counter = 0;
		bool accepted;
		stack.~STACK();
		stack.PushStack(0);
		//stack.displayStack();

		bool decision = true;
		cout << "Checking line " << lineNumber << ": " << w << endl;
		while (w[counter] != NULL)
		{
			//cout << "Tried to read value\n";
			int columnPos;
			char currentChar;
			cout << "\tReading posision " << counter << " as: ( " << w[counter] << " )" << endl;

			if (w[counter] == ' ') {
				counter++;
				outp << " ";
			}
			else
			{
				if (isNumber(w[counter])) // Integer check
				{						//single digits only
					outp << thisOne(w[counter], currentChar); // print character to file, output to std, and save as currentChar		
				}
				else if (isLetter(w[counter]))
				{
					int wordLength = wordCheck(w, counter, special);
					char word[15];
					for (int n = 0; n < wordLength; ++n) {
						word[n] = w[counter + n];
					}
					word[wordLength] = char(0);
					int check = isReserved(word, reservedWords);

					if (check != -1) {
						counter += wordLength - 1;
						outp << reservedWords[check];
						cout << "\t" << reservedWords[check] << " is a reserved word.\n";
						switch (check) {
						case 0: currentChar = 'p'; break;
						case 1: currentChar = 'v'; break;
						case 2: currentChar = 'g'; break;
						case 3: currentChar = 'e'; break;
						case 4: currentChar = 'i'; break;
						case 5: currentChar = 'w'; break;
						}
						stack.PushStack(8);//REMOVE ONCE Table checking is impelmented
					}
					else
					{
						int programLocation = stack.PopStack();
						stack.PushStack(programLocation);
						//if you are at a location in the program that requires a reseved word to follow and it does not, return an error
						if (lineNumber == 1 && programLocation == 0) {
							return displayError("program", lineNumber);
						}
						else if (programLocation == 1) { //the posInfo = :
							return displayError("integer", lineNumber);
						}
						else if (programLocation == 2) {
							return displayError("write", lineNumber);
						}
						// ---------------------------------
						//counter = oringinalCounter;
						outp << thisOne(w[counter], currentChar);
						if (currentChar != 'a' && currentChar != 'b' && currentChar != 'c') return displayError("a, b, or c", lineNumber);
					}

				}
				else
				{
					outp << thisOne(w[counter], currentChar);
				}

				counter++;

				cout << "\t\t" << currentChar << " is the current character about to be checked.\n";
				/* NOT COMPLETED
				// Detect and display FIRST Errors not found in the Reserve word check
				int programLocation = stack.PopStack();
				stack.PushStack(programLocation);
				//if you are at a location in the program that requires a reseved word to follow and it does not, return an error
				switch (programLocation) {
				case('I'): case('G'): case('D'): case('A'):	case('O'):
				switch (currentChar){
				case('a'):case('b'):case('c'): break;
				default:
				return displayError("a, b, or c", lineNumber);
				}
				break;
				case('L'): case('M'):
				if (currentChar >= '0' && currentChar <= '9')break; else return displayError("1 or 2 or ...", lineNumber);
				break;
				case('K'):
				switch (currentChar) {
				case('+'):case('-'): break;
				default:
				return displayError("+ or -", lineNumber);
				}
				break;
				}

				*/
				columnPos = getColumnPosition(currentChar);

				//	cout << "columnPos: " << columnPos << endl;
				//	system("pause");
				//
				//Table checking section
				/*
				int workingInt = stack.PopStack();
				posInfo = intFromTable(workingInt, columnPos);

				if (posInfo / 100 == 1)
				{
				stack.PushStack(workingInt);
				stack.PushStack(columnPos);
				stack.PushStack((posInfo % 100));
				counter++;
				stack.displayStack();
				}
				else if (posInfo / 100 == 2)
				{
				bool notShift = true;
				int langRow;
				while (notShift) {
				stack.PushStack(workingInt);
				langRow = (posInfo % 200) - 1;

				for (int i = 0; i < ((langValues[(posInfo % 200) - 1][1]) * 2); i++)
				{
				stack.PopStack();
				}

				workingInt = stack.PopStack();
				posInfo = intFromTable( workingInt, langValues[langRow][0] );

				stack.PushStack(workingInt);
				stack.PushStack(langValues[langRow][0]);
				stack.PushStack(posInfo % 300);

				stack.displayStack();
				workingInt = stack.PopStack();
				posInfo = intFromTable( workingInt, columnPos );
				if (posInfo / 100 == 1 || posInfo == 999) {
				stack.PushStack(workingInt);
				notShift = false;
				}
				}
				}
				//
				// Check if
				*/

			}
			if (posInfo == 999) {
				accepted = true;
				decision = false;
			}
			else if (posInfo == -1) {
				accepted = false;
				decision = false;
			}
		}

		if (accepted) {
			cout << "This line is accepted.\n\n";
		}
		else if (!accepted) {
			cout << "This line is not accepted.\n\n";
		}
		system("pause");
		outp << endl;
		lineNumber++;
		inp.getline(w, 200);
	}

	inp.close();
	outp.close();

	cout << "\nYour program looks good!\n\n\tTranslating into C++ . . .\n";
	inp.open("finalv2.txt", ios::in);	//open the file that includes the strings to check
	outp.open("finalv4.txt", ios::out);

	cout << "#include  <iostream>" << endl;
	outp << "#include  <iostream>" << endl;
	cout << "using namespace  std;" << endl;
	outp << "using namespace  std;" << endl;
	cout << "int main()" << endl;
	outp << "int main()" << endl;
	cout << "{" << endl;
	outp << "{" << endl;
	//
	// Translating Code
	//
	/*
	inp.getline(w, 200);
	while (!inp.eof())				//loops untill End Of File is read
	{
	int posInfo = 0, counter = 0;
	bool accepted;
	stack.~STACK();
	stack.PushStack(0);
	stack.displayStack();

	bool decision = true;
	cout << "Checking line: " << w;
	while (w[counter] != NULL)
	{
	//cout << "Tried to read value\n";
	int columnPos;
	char currentChar;
	cout << "Read ( " << w[counter] << " )" << endl;

	if (isLetter(w[counter]))
	{
	char word[10];
	int n = 0;
	int oringinalCounter = counter;
	while (!isSpecial(w[counter], special) && w[counter] != ' ' && w[counter] != NULL) {
	word[n] = w[counter];
	counter++; n++;
	}
	counter--;
	word[n] = char(0);
	int check = isReserved(word, reservedWords);
	if (check != -1) {
	outp << reservedWords[check];
	cout << reservedWords[check] << " is a reserved word.\n";
	switch (check) {
	case 0: //read program
	case 1: //read var
	inp.getline(w, 200);

	break;
	case 2: currentChar = 'g'; break;
	case 3: currentChar = 'e'; break;
	case 4: currentChar = 'i'; break;
	case 5: currentChar = 'w'; break;
	}
	}
	else
	{
	counter = oringinalCounter;
	currentChar = w[counter];
	outp << currentChar;
	//	system("pause");
	}

	}
	}
	inp.getline(w, 200);
	}
	*/
	cout << "return 0 ;" << endl;
	outp << "return 0 ;" << endl;
	cout << "}" << endl;
	outp << "}" << endl;
	cout << "\nTranslating into C++ code complete!\n";
	inp.close();
	outp.close();
	system("pause"); //terminate the program
	return 0;
}