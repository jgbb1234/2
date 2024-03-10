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
char consonants[3];
char vowel;
bool hasWildCard;

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

string decryptPuzzle(char encryptedPuzzle[]) {
    string decryptedPuzzle = encryptedPuzzle;
    for (int i = 0; i < decryptedPuzzle.length(); i++) {
        if (isalpha(decryptedPuzzle[i])) {
            decryptedPuzzle[i] = toupper(decryptedPuzzle[i]);
            decryptedPuzzle[i] -= 5;
            if (decryptedPuzzle[i] < 'A') {
                decryptedPuzzle[i] += 26;
            }
        }
    }
    return decryptedPuzzle;
}

string blankOutPuzzle(char puzzle[]) {
    string blankedPuzzle = puzzle; // Create a copy of the original puzzle
    for (int i = 0; i < strlen(puzzle); i++) {
        if (puzzle[i] != ' ' && puzzle[i] != '-') {
            blankedPuzzle[i] = '#'; // Replace non-space and non-dash characters with #
        }
    }
    return blankedPuzzle; // Return the modified puzzle
}


void selectAndDisplayPuzzle() {
    for (int i = 0; i < 1125; i++) {
        if (puzzles[i].category == categoryChoiceName) {
            puzzleChoice = puzzles[i];
            break; // Once a puzzle with the correct category is found, exit the loop
        }
    }

    // Decrypt the puzzle and store it in a local variable
    string decrypted = decryptPuzzle(puzzleChoice.puzzle);

    // Copy the decrypted puzzle to the decryptedPuzzle array
    strcpy(decryptedPuzzle, decrypted.c_str());

    cout << "The puzzle to start with is: " << decrypted << endl;
}

string revealLetters(char puzzle[]) {
    cout << "Revealing the Letters (R, S, T, L, N, E) ..." << endl;

    string lettersToReveal = "RSTLNE";
    for (int i = 0; i < strlen(puzzle); i++) {
        if (lettersToReveal.find(toupper(puzzle[i])) != string::npos) {
            puzzle[i] = toupper(puzzle[i]);
        }
    }
    cout << puzzle << endl;
    return puzzle;
}

bool isConsonant(char c) {
    // Convert the character to lowercase for easier comparison
    c = tolower(c);

    // Check if the character is an alphabet and not a vowel
    if (isalpha(c) && c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
        return true;
    }
    return false;
}

bool isVowel(char c) {
    // Convert the character to lowercase for easier comparison
    c = tolower(c);

    // Check if the character is an alphabet and is a vowel
    if (isalpha(c) && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')) {
        return true;
    }
    return false;
}

void getHasWildCard(){
  int choice;
  do{
    cout << "Do you have the wildcard? (0-No, 1-Yes)";
    cin >> choice;
  }while(choice != 0 || choice != 1);  

  if (choice == 1)
    hasWildCard = true;
  if (choice == 2)
    hasWildCard = false;
} 



void choose3ConsonantsAnd1Vowel(){
    int i = 0;
    char character = '\0';
  
    while (strlen(consonants) < 3){
        cout << "Enter a consonant: ";
        char ch;
        cin >> ch;
        if (isConsonant(ch)){
            consonants[i] = ch;
            i++;
        }
    }
    
    while (isVowel(character) != true){
        cout << "Enter a consonant: ";
        cin >> character;
        if (isVowel(character)){
            vowel = character;
        }
    }

    getHasWildCard();
    if (hasWildCard == true){
      
    }

    if (hasWildCard == false){
      
    }
}


int main() {
  std::cout << "Hello World!\n";
}