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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

bool isNumber(char temp) {
	bool outcome;
	(temp >= '0' && temp <= '9')? outcome = true: outcome = false ;
	return outcome;
}

bool isLetter(char temp) {
	bool outcome;
	((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z'))? outcome = true : outcome = false;
	return outcome;
}

bool isSpecial(char temp, char spec[]) {
	for (int i = 0; i < 10; ++i) {			// Special symbol check
		if (spec[i] == temp) return true;
	}
	return false;
}

int isReserved(char test[], char set[][10]) {
	for (int n = 0; n < 4; n++) {	//Reserved word check
		if (test[0] == set[n][0]) {
			int counter = 0;
			bool check = true;
			for each (char temp in set[n])
			{
				if (test[counter] != temp) {
					if (temp != '\0') {
						check = false;
						break;
					}
				}
				counter++;
			}
			if (check == true) { return n; }
			return -1;
		}
	}
	return -1;
}

int main() {
	char reservedWords[4][10] = { "cout<<","for","int","while" };
	char special[10] = { '+' , '=' , '*' , '-' , ';' , '(' , ')' , ',' , '{' , '}' };
	char w[200];

	fstream inp, outp;				//base file

	inp.open("finalv1.txt", ios::in);	//open the file that includes the strings to check
	outp.open("finalv2.txt", ios::out);

	inp.getline(w, 200);
	while (!inp.eof())				//loop through the lines in the text file
	{
		int i = 0;
		while (w[i] != NULL)		//loops through character in each line
		{
			if (w[i] == '/' && w[i + 1] == '/') {
				i+=2;
				while (w[i] != '/' && w[i + 1] != '/') {
					
					if (w[i] == '\0') {
						inp.getline(w, 200);
						break;
					}
					i++;
				} 
				break; //skips any commented code & gets next line
			}
			else if (w[i] == ' ') {
				//does nothing but get next char
			}
			else if (isNumber(w[i])) // Integer check
			{						//single digits only
				outp << w[i] << " ";
				cout << w[i] << " ";
			}
			else if (isLetter(w[i])) {
				char word[15];
				int n = 0;
				while (!isSpecial(w[i], special) && w[i] != ' ' && w[i] != '\0') {
					word[n] = w[i];
					i++; n++;
				}
				i--;
				word[n] = char(0);
				//int check = isReserved(word, reservedWords);
				//if (check != -1) {
			//		outp << reservedWords[check];
			//   	cout << reservedWords[check];
			//	}
			//	else
			//	{
					cout << word;
					outp << word;
			//	}
					if (w[i + 1] != NULL) {
						outp << " ";
						cout << " ";
					}else{
						outp << endl;
						cout << endl;
					}
			}
			else
			{
				//cout << "Special\n";
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
	//terminate the program
	std::system("pause");
	return 0;
}