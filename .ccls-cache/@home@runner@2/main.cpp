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
  char puzzle [80];
};


string categories[19];

void readCategories(){
  ifstream inputFile("Categories.txt");
  if (!inputFile) {
      cerr << "Error: Unable to open Categories.txt" << endl;
      exit(1);
  }

  for (int i = 0; i <= 19; i++) {
    getline(inputFile, categories[i]);
  }

  inputFile.close();
}

void readPuzzles(){
  ifstream inputFile("WOF-Puzzles.txt");
  if (!inputFile) {
      cerr << "Error: Unable to open WOF-Puzzles.txt" << endl;
      exit(1);
  }
}

int main() {
  std::cout << "Hello World!\n";
}