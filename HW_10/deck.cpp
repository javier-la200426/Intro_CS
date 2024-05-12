#include "deck.h"
#include <fstream>
#include <iostream>

using namespace std;


Deck::Deck(string deckFileName) {
  ifstream deckFile(deckFileName);
  if (deckFile.fail()) {
    cerr << "Failed to open deck file: " << deckFileName << endl;
    exit(EXIT_FAILURE);
  }

  int cardNum;
  for (int i = 0; i < MAX_DECK_SIZE; i++) {

    deckFile >> cardNum;
    if (deckFile.eof()) {
      cerr << "File does not contain " << MAX_DECK_SIZE << " cards!" << endl;
      exit(EXIT_FAILURE);
    } else if (deckFile.fail()) {
      cerr << "Failed to read from file: " << deckFileName << endl;
      exit(EXIT_FAILURE);
    }

    deck[i] = new Card(cardNum);
  }

  topCard = 0;
}


Deck::~Deck() {
  for (int i = topCard; i < MAX_DECK_SIZE; i++) {
    delete deck[i];
  }
}


bool Deck::isEmpty() {
  // Completed by Javier Laveaga
  if (topCard >= MAX_DECK_SIZE) { //this is 60
    return true;
  } else {
    return false; 
  }
}


Card* Deck::draw() {
  if (isEmpty()) {
    cerr << "ERROR: Drawing from an empty deck" << endl;
    exit(EXIT_FAILURE);
  }
  //Completed by Javier Laveaga

  Card *CardDrawn = deck[topCard];
  // Jav: use the topCard and change it by 1
  topCard++;

  return CardDrawn; // change this if necessary
}
