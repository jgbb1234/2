#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>

using namespace std;

struct Puzzle {
    string category;
    char puzzle[80];
};

string categories[19];
Puzzle puzzles[1125];
int categoryChoice = 0;
string categoryChoiceName;
Puzzle puzzleChoice;
char decryptedPuzzle[80];

void readCategories() {
    ifstream inputFile("Categories.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open Categories.txt" << endl;
        exit(1);
    }

    for (int i = 0; i < 19; i++) {
        getline(inputFile, categories[i]);
    }

    inputFile.close();
}

void readPuzzles() {
    ifstream inputFile("WOF-Puzzles.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open WOF-Puzzles.txt" << endl;
        exit(1);
    }

    for (int i = 0; i < 1125; i++) {
        getline(inputFile, puzzles[i].category);
        inputFile.getline(puzzles[i].puzzle, 80); // Changed from getline to getline
    }

    inputFile.close();
}

int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void chooseCategories() {
    for (int i = 0; i < 4; i++) {
        int num = generateRandomNumber(1, 19); // Corrected to generate a random number between 0 and 18
        cout << "Please choose from one of the following categories:" << endl;
        cout << i + 1 << ". " << categories[num] << endl;
    }

    cout << "Enter the number of the category you would like to play: ";
    cin >> categoryChoice;
    cout << "Category chosen for bonus round is: " << categories[categoryChoice - 1] << endl;

    categoryChoiceName = categories[categoryChoice]; // Corrected index to match user input
}

void decryptPuzzle(char encryptedPuzzle[]) {
    for (int i = 0; i < strlen(encryptedPuzzle); i++) {
        if (isalpha(encryptedPuzzle[i])) {
            encryptedPuzzle[i] = toupper(encryptedPuzzle[i]);
            encryptedPuzzle[i] -= 5;
            if (encryptedPuzzle[i] < 'A') {
                encryptedPuzzle[i] += 26;
            }
        }
    }
}

void blankOutPuzzle(char puzzle[]) {
    for (int i = 0; i < strlen(puzzle); i++) {
        if (puzzle[i] != ' ' && puzzle[i] != '-') {
            puzzle[i] = '#';
        }
    }
}

void selectAndDisplayPuzzle() {
    for (int i = 0; i < 1125; i++) {
        if (puzzles[i].category == categoryChoiceName) {
            puzzleChoice = puzzles[i];
            break; // Once a puzzle with the correct category is found, exit the loop
        }
    }

    decryptPuzzle(puzzleChoice.puzzle);
    strcpy(decryptedPuzzle, decryptPuzzle(puzzleChoice.puzzle));
    blankOutPuzzle(puzzleChoice.puzzle);

    cout << "The puzzle to start with is: " << puzzleChoice.puzzle << endl;
}

void revealLetters(char puzzle[]) {
    string lettersToReveal = "RSTLNE";
    for (int i = 0; i < strlen(puzzle); i++) {
        if (lettersToReveal.find(puzzle[i]) != string::npos) {
            puzzle[i] = toupper(puzzle[i]);
        }
    }
}

void revealLetters(){
  cout << "Revealing R, S, T, L, N, E ..." << endl;
  
  
}

int main() {
  std::cout << "Hello World!\n";
}