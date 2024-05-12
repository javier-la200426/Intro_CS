#include "card.h"
#include "hand.h"
#include <iostream>

using namespace std;


Hand::Hand(Card* c1, Card* c2, Card* c3, Card* c4, Card* c5) {
  cards[0] = c1;
  cards[1] = c2;
  cards[2] = c3;
  cards[3] = c4;
  cards[4] = c5;
}


Hand::~Hand() {
  for (int i = 0; i < HAND_SIZE; i++) {
    delete cards[i];
  }
}


bool Hand::isWinningHand() {
  // Completed by Javier Laveaga

  int left_num = -1; //so that in first iteration
    //it doesnt return false if cur num is 0
  for (int i = 0; i < HAND_SIZE; i++) { //that is 5
    int cur_num = cards[i]->getNum();
    if (i > 0) { //so that I don't compare 0th element to -1th element
      left_num = cards[i-1]->getNum();
    }
    if (cur_num < left_num) { 
      return false;
    }
  }
  return true;
}


Card* Hand::replaceCard(Card* newCard) {
  print(); 
  cout << endl;
  //Completed by Javier Laveaga
  int index_discard;
  //dont add more print statements after the one below
  cout << "Enter the index of the card you'd like to discard: ";
  cin >> index_discard;
  Card *replaced_card = cards[index_discard]; //save the card to be replaced
  cards[index_discard] = newCard; //replace card
  return replaced_card;
}


void Hand::print() {
  for (int i = 0; i < HAND_SIZE; i++) {
    if (cards[i] == NULL) {
      cerr << "ERROR: hand does not have " << HAND_SIZE << " cards!" << endl;
      exit(EXIT_FAILURE);
    }
  }

  // print Top Edge
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getTopEdge();
  }
  cout << endl;

  // print Blank Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBlankLine();
  }
  cout << endl;

  // print Number Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getNumberLine();
  }
  cout << endl;

  // print Blank Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBlankLine();
  }
  cout << endl;

  // print Bottom Edge
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBottomEdge();
  }
  cout << endl;

  // print index numbers
  for (int i = 0; i < HAND_SIZE; i++) {
    cout << "   ";
    if (i > 0) {
      cout << "    ";
    }
    cout << i;
  }
  cout << endl;
}
