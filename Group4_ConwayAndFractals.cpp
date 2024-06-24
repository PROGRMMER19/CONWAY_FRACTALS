#include <iostream>
#include <limits>
#include <string>
#include <cstring>

using namespace std;

#define MAXIMUM 100
/*Function that displays the choices which are mathematical sequences*/
void menu() {
    cout << "----MAIN MENU----" << endl;
    cout << "[1] Conway's Sequence (look-and-say)" << endl;
    cout << "[2] Fractals" << endl;
    cout << "[3] Exit Program" << endl;
    cout << "Choose a sequence to be displayed (1-3): ";
}
/*Function that validates an integer input*/
void intValidation(int& num) {
    while (true) {
        if (cin >> num) {
            break;
        }else {
            cout << "Input must be a number, try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
/*Function that validates an string input*/
void strValidation(string& input) {
    bool validation = false;

    while (true) {
        getline(cin, input);
        for (char c : input) {
            if (!(isalpha(c) || isspace(c))) {
                break;
            }else {
                validation = true;
            }
        }
        if (!validation) {
            cout << "Input must be a string, try again: ";
        }else {
            break;
        }
    }
}
/*Function that checks if an input is either yes or no*/
void userValidation(string& input) {
    strValidation(input);
    while (true) {
        if (!(input == "yes" || tolower(input == "YES") || tolower(input == "Yes") || input == "no" || tolower(input == "NO") || tolower(input == "No"))) {
            cout << "Invalid, type only either \"yes\" or \"no\": ";
        }else {
            break;
        }
    }
}
/*Function that terminates the program*/
void exit(bool& termination) {
    string exitChoice;

    cout << "Are you sure do you want to exit the program? (yes/no): ";
    cin.ignore();
    userValidation(exitChoice);

    system("cls");

    if (exitChoice == "yes" || tolower(exitChoice == "YES") || tolower(exitChoice == "Yes")) {
        termination = true;
        cout << "Program has been successfully terminated." << endl;
    }
}

void printTerms(int terms[], int length) {
    for (int i = 0; i < length; ++i) {
        cout << terms[i];
    }
    cout << endl;
}
/*Function that performs the Conway's Sequence*/
void conwaySequence() {
    int numTerms, firstTerm, quantity;

    cout << "How many terms should the program generate? (1-" << MAXIMUM << "): ";
    while (true) {
        intValidation(numTerms);
        if (numTerms < 1 || numTerms > MAXIMUM) {
            cout << "Length should only be from 1-" << MAXIMUM << ", please try again: ";
        }else {
            break;
        }
    }

    cout << "Enter a number from 1-9: ";
    while (true) {
        intValidation(firstTerm);
        if (firstTerm <= 0) {
            cout << "Number 0 and below is not allowed in this sequence, please try again: ";
        }else if (firstTerm > 9) {
            cout << "First term should be a one-digit number only, please try again: ";
        }else {
            break;
        }
    }

    cout << endl;
    cout << "Displayed below are " << numTerms << " terms starting from number " << firstTerm << ":" << endl;
    
    int currentTerm[MAXIMUM] = {firstTerm}, nextTerm[MAXIMUM];
    int currentLength = 1, nextLength;

    printTerms(currentTerm, currentLength);                     //Prints the first term

    for (int i = 1; i < numTerms; i++) {
        quantity = 1;                                           //Initial quantity
        nextLength = 0;
        for (int j = 1; j <= currentLength; j++) {
            if (j < currentLength && currentTerm[j] == currentTerm[j - 1]) {
                quantity++;                                     //Quantity increases when there are identical digits in the array 
            }else {
                nextTerm[nextLength++] = quantity;              //Inserts the quantity of the first digit from the previous term into the array
                nextTerm[nextLength++] = currentTerm[j - 1];    //Inserts the first digit of the previous term into the array
                quantity = 1;                                   //Quantity goes back to its initial value
            }
        }
        printTerms(nextTerm, nextLength);                       //Prints the terms consecutively which corresponds to the first term
        currentLength = nextLength;
        memcpy(currentTerm, nextTerm, nextLength * sizeof(int));//Copies the content and the amount of bytes from the "nextTerm" array to the "currentTerm" array
    }

    cout << endl;
    cout << "Press enter to go back to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

int main(){
    int option;
    bool termination = false;

    do {
        menu();
        while (true) {
            intValidation(option);
            if (option < 1 || option > 3) {
                cout << "Input must be from 1-3, please try again: ";
            }else {
                break;
            }
        }

        system("cls");

        switch (option) {
        case 1:
            conwaySequence();
            break;
        case 2:
            break;
        case 3:
            exit(termination);
            break;
        }
    } while (!termination);
}