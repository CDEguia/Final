#pragma once
#ifndef Functions
#define Functions
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
		//std::cout << "Pushed : " << x << "\n";
	}
	void displayStack() {
		std::cout << "Stack: ";
		NODE *temp;
		temp = new (NODE);
		temp = top;
		std::cout << temp->info << " ";
		while (temp->next != NULL) {
			temp = temp->next;
			std::cout << temp->info << " ";

		}
		std::cout << "\n";

	}
	int PopStack()							// Returns Value deletes node
	{
		NODE *temp = top;
		int x = temp->info;
		top = temp->next;					// Replaces the top of stack node 
		delete temp;						// Deletes the old node on top of stack
											//std::cout << "Popped :" << x << "\n";
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

int wordCheck(char line[], int locToCheck, char specialSet[]) {
	int n = 0;
	while (!isSpecial(line[locToCheck], specialSet) && line[locToCheck] != ' ' && line[locToCheck] != NULL) {
		locToCheck++; n++;
	}
	return n;
}

int isReserved(char test[], char set[][10]) {
	for (int n = 0; n < 6; n++) {	//Reserved word check
		if (test[0] == set[n][0]) {
			int loc = 0;
			bool check = true;
			//for each (char temp in set[n])
			for (int x = 0; x < 10; x++)
			{
				char temp = set[n][x];
				if (test[loc] != temp) {
					if (temp != '\0') {
						check = false;
						break;
					}
				}
				loc++;
			}
			if (check == true) { return n; }
			return -1;
		}
	}
	return -1;
}

int getColumnPosition(char test) {
	switch (test)
	{
	case 'p': return 0;
	case 'v': return 1;
	case 'g': return 2;
	case 'e': return 3;
	case 'i': return 4;
	case 'w': return 5;
	case '+': return 6;
	case '-': return 7;
	case '*': return 8;
	case '/': return 9;
	case ':': return 10;
	case '=': return 11;
	case ',': return 12;
	case '(': return 13;
	case ')': return 14;
	case ';': return 15;
	case '0': return 16;
	case '1': return 17;
	case '2': return 18;
	case '3': return 19;
	case '4': return 20;
	case '5': return 21;
	case '6': return 22;
	case '7': return 23;
	case '8': return 24;
	case '9': return 25;
	case 'a': return 26;
	case 'b': return 27;
	case 'c': return 28;
	case 'P': return 29;
	case 'I': return 30;
	case 'C': return 31;
	case 'G': return 32;
	case 'T': return 33;
	case 'D': return 34;
	case 'S': return 35;
	case 'H': return 36;
	case 'A': return 37;
	case 'W': return 38;
	case 'E': return 39;
	case 'J': return 40;
	case 'F': return 41;
	case 'N': return 42;
	case 'K': return 43;
	case 'M': return 44;
	case 'L': return 45;
	case 'O': return 46;
	default: return 47;
	}
}

void errorPrompt() {
	for (int i = 0; i < 3; i++) {
		(i == 1) ? std::cout << "** ERROR **\n" : std::cout << "*\n";
	}
}

int displayError(char errorMessage[], int online) {
	errorPrompt();
	std::cout << errorMessage << "\tis expected on line: " << online << "\n";
	errorPrompt();
	system("pause");
	return 0;
}

int intFromTable(int row, int column) {
	int table[86][49] = {
		{ 102 , -1 , -1	, -1 , 107 , 111 ,117 , 118	, -1 , -1 , -1 , -1	, -1 , 115 , -1	, -1 , -1 , -1 , 122 , 123 , 124 , 125 , 126 , 127 , 128 , 129 , 130 , 131 , 119 , 120 , 121 , 301 , 305 , -1 , -1 , -1 , 306 ,	310	, -1 , 309 , 308 , -1 , 312 , 313 , 314 , 316 , -1 , 304 , 303 },
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
	return table[row][column];
}

char thisOne(char single, char& testChar) {
	testChar = single;
	return single;
}

#endif
