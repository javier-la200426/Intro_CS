#include "hand.h"
#include <iostream>
#include <fstream>

using namespace std;


const int CARDS_TO_READ = 5;


int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " filename" << endl;
    exit(EXIT_FAILURE);
  }
  string deckFileName(argv[1]);

  ifstream deckFile(deckFileName);
  if (deckFile.fail()) {
    cerr << "Failed to open deck file: " << deckFileName << endl;
    exit(EXIT_FAILURE);
  }

  int deck_contents[CARDS_TO_READ];
  for (int i = 0; i < CARDS_TO_READ; i++) {
    deckFile >> deck_contents[i];

    if (deckFile.eof()) {
      cerr << "File does not contain " << CARDS_TO_READ << " cards!" << endl;
      exit(EXIT_FAILURE);
    } else if (deckFile.fail()) {
      cerr << "Failed to read from file: " << deckFileName << endl;
      exit(EXIT_FAILURE);
    }
  }
  //jav: code above is just reading in the file into an array of integers

  //First 5 cards in that array are being placed in hand object
  Hand hand(new Card(deck_contents[0]),
            new Card(deck_contents[1]),
            new Card(deck_contents[2]),
            new Card(deck_contents[3]),
            new Card(deck_contents[4]));

  // TODO: write code that tests the Hand
  // particularly the isWinningHand() and replaceCard() methods
  //cout << "FAILED: No tests are implemented yet!!" << endl;

  //Test if the hand is a winning hand
  bool isWinningHand = hand.isWinningHand();
  if (isWinningHand) {
    cout << "The hand is a winning hand" << endl;
  } else {
    cout << "Not a winning hand" << endl;
  }

  cout << "Failed tests are listed above. If there is no output, "
       << "then it all succeeded!" << endl;
  return 0;
}
