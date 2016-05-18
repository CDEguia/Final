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
#include <string>

using namespace std;
class STACK									// Create a Linklist Stack for the evaluation
{
private:
	struct NODE {							// Create a data type containing
		int info;								// the info to be retreved / saved
		NODE *next;							// the link to the next item in the list
	};
	NODE *top;								// Holds the current top of stack
	NODE *temp;
public:
	void CreateTop() {						// Creates a new Node
		NODE *temp;
		temp = new (NODE);
		temp->next = top;
		top = temp;
	}
	void PushStack(int x) {					// Used to push a new integer onto the stack
		CreateTop();
		top->info = x;
		//cout << "Pushed : " << x << endl;
	}
	void displayStack() {
		cout << "Stack: ";
		NODE *temp;
		temp = new (NODE);
		temp = top;
		cout << temp->info << " ";
		while (temp->next != NULL) {
			temp = temp->next;
			cout << temp->info << " ";

		}
		cout << endl;

	}
	int PopStack()							// Returns Value deletes node
	{
		NODE *temp = top;
		int x = temp->info;
		top = temp->next;					// Replaces the top of stack node 
		delete temp;						// Deletes the old node on top of stack
											//cout << "Popped :" << x << endl;
		return x;
		// Returns value
	}
	bool isEmpty()
	{
		if (top->info == NULL) return true;
		else return false;
	}

	~STACK() {								// Deletes any nodes left in the stack
		NODE *temp = top;
		while (temp != NULL) {
			temp = temp->next;
			delete top;
			top = temp;
		}
	}
}; // End of Stack

bool isNumber(char temp) {
	bool outcome;
	(temp >= '0' && temp <= '9') ? outcome = true : outcome = false;
	return outcome;
}

bool isLetter(char temp) {
	bool outcome;
	((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z')) ? outcome = true : outcome = false;
	return outcome;
}

bool isSpecial(char temp, char spec[]) {
	for (int i = 0; i < 10; ++i) {			// Special symbol check
		if (spec[i] == temp) return true;
	}
	return false;
}

int main() {
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
				i += 2;
				while (w[i] != '/' && w[i + 1] != '/') {
					if (w[i] == NULL) {
						inp.getline(w, 200);
						break;
					}
					i++;
				}
				break; //skips any commented code & gets next line
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
				char word[15];
				int n = 0;
				while (!isSpecial(w[i], special) && w[i] != ' ' && w[i] != NULL) {
					word[n] = w[i];
					i++; n++;
				}
				i--;
				word[n] = char(0); //adds the terminal character to the end of the word
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

	cout << "Your file has been cleaned up. The new version is now stored in: finalv2.txt";
	std::system("pause");
	cout << "File Verification...";

	inp.open("finalv2.txt", ios::in);	//open the file that includes the strings to check

	STACK stack;
	STACK tempStack;
	stack.PushStack(0);
	stack.displayStack();
	int columnPos, rowPos, workingInt, workingInt2, posInfo = 0, toPop, langRow, counter = 0;
	bool accepted, decision = true, notShift = true;
	string line;
	char workingChar;

	int table[16][11] = {
		{ 105,-1,-1,-1,-1,104,-1,-1,301,302,303 },
		{ -1,106,107,-1,-1,-1,-1,999,-1,-1,-1 },
		{ -1,203,203,108,109,-1,203,203,-1,-1,-1 },
		{ -1,206,206,206,206,-1,206,206,-1,-1,-1 },
		{ 105,-1,-1,-1,-1,104,-1,-1,310,302,303 },
		{ -1,208,208,208,208,-1,208,208,-1,-1,-1 },
		{ 105,-1,-1,-1,-1,104,-1,-1,-1,311,303 },
		{ 105,-1,-1,-1,-1,104,-1,-1,-1,312,303 },
		{ 105,-1,-1,-1,-1,104,-1,-1,-1,-1,313 },
		{ 105,-1,-1,-1,-1,104,-1,-1,-1,-1,314 },
		{ -1,106,107,-1,-1,-1,115,-1,-1,-1,-1 },
		{ -1,201,201,108,109,-1,201,201,-1,-1,-1 },
		{ -1,202,202,108,109,-1,202,202,-1,-1,-1 },
		{ -1,204,204,204,204,-1,204,204,-1,-1,-1 },
		{ -1,205,205,205,205,-1,205,205,-1,-1,-1 },
		{ -1,207,207,207,207,-1,207,207,-1,-1,-1 } };
	int langValues[8][2] = { { 8,3 },{ 8,3 },{ 8,1 },{ 9,3 },{ 9,3 },{ 9,1 },{ 10,3 },{ 10,1 } };

	getline(inp, line, '\n');		//Get first line of file
	while (!inp.eof())				//loops untill End Of File is read
	{
		while (decision)
		{
			//cout << "Tried to read value\n";
			cout << "Read : " << line[counter] << endl;
			switch (line[counter])
			{
			case 'i': columnPos = 0; break;
			case '+': columnPos = 1; break;
			case '-': columnPos = 2; break;
			case '*': columnPos = 3; break;
			case '/': columnPos = 4; break;
			case '(': columnPos = 5; break;
			case ')': columnPos = 6; break;
			case '$': columnPos = 7; break;
			case 'E': columnPos = 8; break;
			case 'T': columnPos = 9; break;
			case 'F': columnPos = 10; break;
			}

			workingInt = stack.PopStack();

			posInfo = table[workingInt][columnPos];
			if (posInfo / 100 == 1)
			{
				stack.PushStack(workingInt);
				stack.PushStack(columnPos);
				stack.PushStack((posInfo % 100));
				counter++;
				stack.displayStack();
			}

			if (posInfo / 100 == 2)
			{
				while (notShift) {
					if (posInfo / 100 == 2) {
						stack.PushStack(workingInt);
						langRow = (posInfo % 200) - 1;
						toPop = (langValues[(posInfo % 200) - 1][1]) * 2;

						for (int i = 0; i < toPop; i++)
						{
							stack.PopStack();
						}
						workingInt2 = workingInt;
						workingInt = stack.PopStack();
						posInfo = table[workingInt][langValues[langRow][0]];

						stack.PushStack(workingInt);

						stack.PushStack(langValues[langRow][0]);

						stack.PushStack(posInfo % 300);

						stack.displayStack();
						workingInt = stack.PopStack();
						posInfo = table[workingInt][columnPos];
						if (posInfo / 100 == 1 || posInfo == 999) {
							stack.PushStack(workingInt);
							notShift = false;
						}
					}
				}
				notShift = true;

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
			cout << "This value is accepted.\n";
		}
		else if (!accepted) {
			cout << "This value is not accepted.\n";
		}

		getline(inp, line, '\n');	//Get NEXT line of file
	}

	std::system("pause"); //terminate the program
	return 0;
}