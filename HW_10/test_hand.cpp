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

  //Testing the isWinningHand
  //looping over integer array and seeing if they are in ascending order
  bool ascending = true;
  int left_num = -1;
  for (int i = 0; i < CARDS_TO_READ; i++) { //that is 5
    int cur_num = deck_contents[i];
    if (i > 0) { //so that I don't compare 0th element to -1th element
      left_num = deck_contents[i - 1];
    }
    if (cur_num < left_num) { 
      ascending = false;
    }
  }
  
  Hand hand(new Card(deck_contents[0]),
            new Card(deck_contents[1]),
            new Card(deck_contents[2]),
            new Card(deck_contents[3]),
            new Card(deck_contents[4]));

  bool isWinningHand = hand.isWinningHand();
  /*
  if (isWinningHand) {
    cout << "The hand is a winning hand" << endl;
  } else {
    cout << "Not a winning hand" << endl;
  }
  */
 
  if (ascending != isWinningHand) {
    if (ascending == true) {
      cout << "Failed: expected a winning hand" << endl;
    } else {
      cout << "Failed: expected a losing hand" << endl;
    }
  }

  // particularly the isWinningHand() and replaceCard() methods
  //cout << "FAILED: No tests are implemented yet!!" << endl;

  //Testing the replace Card method
  Card *replaced_card = hand.replaceCard(new Card (62)); //card whose number is 62
  hand.print(); // print hand after replacement
  int num_replaced = replaced_card->getNum(); // get number
  cout << num_replaced << endl;

  

  cout << "Failed tests are listed above. If there are no fail messages, " 
  << "the correct card was inserted, and the number of the previous card is"
  << " printed, then it all succeeded!" << endl;
  return 0;
}
