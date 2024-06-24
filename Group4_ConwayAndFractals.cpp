#include <iostream>
#include <limits>
#include <string>
#include <cstring>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;

#define MAX_TERMS 100
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
        }
        else {
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
            }
            else {
                validation = true;
            }
        }
        if (!validation) {
            cout << "Input must be a string, try again: ";
        }
        else {
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
        }
        else {
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

    cout << "How many terms should the program generate? (1-" << MAX_TERMS << "): ";
    while (true) {
        intValidation(numTerms);
        if (numTerms < 1 || numTerms > MAX_TERMS) {
            cout << "Length should only be from 1-" << MAX_TERMS << ", please try again: ";
        }
        else {
            break;
        }
    }

    cout << "Enter a number from 1-9: ";
    while (true) {
        intValidation(firstTerm);
        if (firstTerm <= 0) {
            cout << "Number 0 and below is not allowed in this sequence, please try again: ";
        }
        else if (firstTerm > 9) {
            cout << "First term should be a one-digit number only, please try again: ";
        }
        else {
            break;
        }
    }

    cout << endl;
    cout << "Displayed below are " << numTerms << " terms starting from number " << firstTerm << ":" << endl;

    int currentTerm[MAX_TERMS] = { firstTerm }, nextTerm[MAX_TERMS];
    int currentLength = 1, nextLength;

    printTerms(currentTerm, currentLength);                     //Prints the first term

    for (int i = 1; i < numTerms; i++) {
        quantity = 1;                                           //Initial quantity
        nextLength = 0;
        for (int j = 1; j <= currentLength; j++) {
            if (j < currentLength && currentTerm[j] == currentTerm[j - 1]) {
                quantity++;                                     //Quantity increases when there are identical digits in the array 
            }
            else {
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


// Define the grid size
const int GRID_SIZE = 80;
const int MAX_DEPTH = 4;

// Define a point as a structure
struct Point {
    double x, y;
};

// Function prototypes
void drawKochCurve(char grid[][GRID_SIZE], const Point& p1, const Point& p2, int depth);
void drawKochSnowflake(char grid[][GRID_SIZE], const Point& center, double length, int depth);
void printGrid(char grid[][GRID_SIZE]);


// Function to print the grid
void printGrid(char grid[][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            cout << grid[i][j];
        }
        cout << '\n';
    }

    cout << endl;
    cout << "Press enter to go back to the main menu...";
    cin.ignore();
    cin.get();
    system("cls");
}

// Function to draw a point on the grid
void drawPoint(char grid[][GRID_SIZE], const Point& p) {
    int x = static_cast<int>(round(p.x));
    int y = static_cast<int>(round(p.y));
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        grid[y][x] = '*';
    }
}

// Function to draw a Koch curve
void drawKochCurve(char grid[][GRID_SIZE], const Point& p1, const Point& p2, int depth) {
    if (depth == 0) {
        drawPoint(grid, p1);
        drawPoint(grid, p2);
    }
    else {
        Point p3, p4, p5;
        double angle = M_PI / 3; // 60 degrees

        // Calculate points p3 and p4 which are one-third and two-thirds of the way from p1 to p2
        p3.x = p1.x + (p2.x - p1.x) / 3.0;
        p3.y = p1.y + (p2.y - p1.y) / 3.0;

        p4.x = p1.x + 2.0 * (p2.x - p1.x) / 3.0;
        p4.y = p1.y + 2.0 * (p2.y - p1.y) / 3.0;

        // Calculate point p5 which forms the peak of the triangle
        p5.x = p3.x + (p4.x - p3.x) * cos(angle) - (p4.y - p3.y) * sin(angle);
        p5.y = p3.y + (p4.x - p3.x) * sin(angle) + (p4.y - p3.y) * cos(angle);

        drawKochCurve(grid, p1, p3, depth - 1);
        drawKochCurve(grid, p3, p5, depth - 1);
        drawKochCurve(grid, p5, p4, depth - 1);
        drawKochCurve(grid, p4, p2, depth - 1);
    }
}

// Function to draw a Koch snowflake
void drawKochSnowflake(char grid[][GRID_SIZE], const Point& center, double length, int depth) {
    // Calculate the vertices of the equilateral triangle
    Point p1, p2, p3;
    double height = sqrt(3.0) * length / 2.0;

    p1.x = center.x - length / 2.0;
    p1.y = center.y + height / 3.0;

    p2.x = center.x + length / 2.0;
    p2.y = center.y + height / 3.0;

    p3.x = center.x;
    p3.y = center.y - 2.0 * height / 3.0;

    drawKochCurve(grid, p1, p2, depth);
    drawKochCurve(grid, p2, p3, depth);
    drawKochCurve(grid, p3, p1, depth);
}

int main() {
    int option;
    bool termination = false;
    // Initialize the grid
    char grid[GRID_SIZE][GRID_SIZE];
    memset(grid, ' ', sizeof(grid));

    // Define the center and the length of the snowflake
    Point center = { GRID_SIZE / 2.0, GRID_SIZE / 2.0 };
    double length = GRID_SIZE / 2.0;

    // Draw the Koch Snowflake
    drawKochSnowflake(grid, center, length, MAX_DEPTH);

    do {
        menu();
        while (true) {
            intValidation(option);
            if (option < 1 || option > 3) {
                cout << "Input must be from 1-3, please try again: ";
            }
            else {
                break;
            }
        }

        system("cls");

        switch (option) {
        case 1:
            conwaySequence();
            break;
        case 2:
            printGrid(grid);
            break;
        case 3:
            exit(termination);
            break;
        }
    } while (!termination);
}