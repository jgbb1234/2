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
string categoriesChoiceNames[2];
Puzzle puzzleChoice;
char decryptedPuzzle[80];
char consonants[4];
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
    cout << "Please choose from one of the following categories:" << endl;
    for (int i = 0; i < 3; i++) {
        int num = generateRandomNumber(0, 18); // Corrected to generate a random number between 0 and 18
        cout << i + 1 << ". " << categories[num] << endl;
        categoriesChoiceNames[i] = categories[num];
    }

    cout << "Enter the number of the category you would like to play:";
    cin >> categoryChoice;
    cout << "Category chosen for bonus round is: " << categoriesChoiceNames[categoryChoice - 1] << endl;

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
    
    cout << "The puzzle to start with is: " << blankOutPuzzle(puzzleChoice.puzzle) << endl;
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
  }while(choice != 0 && choice != 1);  

  if (choice == 1)
    hasWildCard = true;
  if (choice == 2)
    hasWildCard = false;
} 

string revealCharacters(char consonants[], char vowel, char puzzle[]) {
    string revealed;

    for (size_t i = 0; i < strlen(puzzle); ++i) {
        if (puzzle[i] == ' ' || puzzle[i] == '-') {
            revealed += puzzle[i];
        } else {
            bool found = false;
            for (size_t j = 0; j < strlen(consonants); ++j) {
                if (puzzle[i] == consonants[j]) {
                    found = true;
                    break;
                }
            }
            if (!found && puzzle[i] != vowel) {
                revealed += '#';
            } else {
                revealed += puzzle[i];
            }
        }
    }

    return revealed;
}

string uppercaseCharArray(char arr[]) {
    string result;
    size_t length = strlen(arr); // Determine the length of the array
    for (size_t i = 0; i < length; ++i) {
        result += toupper(arr[i]); // Convert each character to uppercase and append to result
    }
    return result;
}

string uppercaseString(const string& str) {
    string result;
    for (char c : str) {
        result += toupper(c); // Convert each character to uppercase and append to result
    }
    return result;
}

void revealPrize() {
    int prize = generateRandomNumber(1, 25);
    if (prize <= 3) {
        cout << "Congratulations! You've won a car!" << endl;
    } else if (prize <= 22) {
        cout << "Congratulations! You've won $40,000.00!" << endl;
    } else if (prize <= 24) {
        cout << "Congratulations! You've won $45,000.00!" << endl;
    } else {
        cout << "Congratulations! You've won the jackpot of $100,000.00!" << endl;
    }
}

void makeGuesses(){
    bool guessedCorrectly = false;
    for (int i = 0; i < 3; i++){
        string guess;
        cout << "You have " << 3 - i << " guesses left. Make a Guess: " << endl;
        cin >> guess;
        string upperGuess = uppercaseString(guess);
        string upperPuzzle = uppercaseCharArray(decryptedPuzzle);
        if (upperGuess == upperPuzzle){
            cout << "You win!!" << endl;
            revealPrize();
            guessedCorrectly = true;
            break; // Exit the loop if the guess is correct
            cout << upperPuzzle; 
        }
    }
    if (!guessedCorrectly) {
        cout << "No more tries! You lose!" << endl;
    }
}

void choose3ConsonantsAnd1Vowel(){
    int i = 0;
    char character = '\0';
  
    while (strlen(consonants) < 3){
        cout << "Enter a consonant: ";
        char ch;
        cin >> ch;
        if (isConsonant(ch)){
            consonants[i] = toupper(ch);
            i++;
        }
    }
    
    while (isVowel(character) != true){
        cout << "Enter a vowel: ";
        cin >> character;
        if (isVowel(character)){
            vowel = toupper(character);
        }
    }

    getHasWildCard();
    if (hasWildCard == true){
      char choice;
      cout << "Choose a fourth consonant" << endl;
      cin >> choice;
      while (isConsonant(choice) != true){
          cout << "Enter a consonant: ";
          cin >> choice;
          if (isVowel(choice)){
              consonants[3] = choice;
          }  
      }
    
      string blankedWord = revealCharacters(consonants, vowel, decryptedPuzzle);
      cout << "The puzzle is: " << blankedWord << endl;
      makeGuesses();
    }

    if (hasWildCard == false){
      string blankedWord = revealCharacters(consonants, vowel, decryptedPuzzle);
      cout << "The puzzle is: " << blankedWord << endl;
      makeGuesses();
    }
}


int main() {
  srand(100);
  readCategories();
  readPuzzles();
  chooseCategories();
  selectAndDisplayPuzzle();
  choose3ConsonantsAnd1Vowel();
}