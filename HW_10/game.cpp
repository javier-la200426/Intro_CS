#include "game.h"
#include <iostream>

using namespace std;


Game::Game(string deckFileName) {
  deck = new Deck(deckFileName); //creates a deck when game is called
  for (int i = 0; i < NUM_PLAYERS; i++) {
    //filling up the array (size =2) of hands
    hands[i] = new Hand(deck->draw(),
                        deck->draw(),
                        deck->draw(),
                        deck->draw(),
                        deck->draw());
  //so now you have 2 hands in the array hands (indeces 0 through 9)
  }
  //now you have a discard pile with the 0,1,2...10th card on top
  discard = new DiscardPile(deck->draw()); //gives 1st card as seed
}


Game::~Game() {
  for (int i = 0; i < NUM_PLAYERS; i++) {
    delete hands[i];
  }
  delete discard;
  delete deck;
}


void Game::play() {
  int playerNum = 0;
  cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
  takeTurn(playerNum);
  cout << endl;

  while (!didPlayerWin(playerNum) && !deck->isEmpty()) {
    //every time playerNum gets to 2, it goes back to 0 with NUM_Players
    //playerNum = 0,1,0,1,0
    playerNum = (playerNum + 1) % NUM_PLAYERS; 
    cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
    takeTurn(playerNum);
    cout << endl;
  }

  if (didPlayerWin(playerNum)) {
    cout << "CONGRATULATIONS PLAYER " << playerNum + 1 << "! YOU WIN!!" << endl;
  } else {
    // deck is empty
    cout << "The deck is empty. IT'S A TIE!" << endl;
  }
}

// completed by Javier Laveaga (jlavea01)
// You should call takeDiscard() and drawFromDeck() from this function.
void Game::takeTurn(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }
  //print the hand of the player. playerNum should be either 0 or 1.
  cout << "Your hand:" << endl;
  hands[playerNum]->print();
  cout << endl;
  cout << "Discard pile:" << endl;
  discard->print();
  cout << endl;

  int choice = 0;
  cout << "Would you like to" << endl;
  cout << " 1. take the top discard?" << endl;
  cout << " 2. draw from the deck?" << endl;

  cout << "Enter the number for your choice: ";
  cin >> choice;
  //keep asking user for input until they give you either 1 or 2.
  while(choice != 1 && choice != 2) {
    cout << "Enter the number for your choice: ";
    cin >> choice;
  }
  cout << endl; //idk 

  if (choice == 1) {
    takeDiscard(playerNum);
  } else if (choice == 2) {
    drawFromDeck(playerNum);
  }
}

//Completed by Javier Laveaga
//Discard pile is face up cards
void Game::takeDiscard(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }
  //acceses the hand of current player
  // new card (argument) is the top card in the discard pile
  // replace Card replaces a card in the hand for the new card
  // saves the card that used to be in the hand in replaced_card
  Card* replaced_card = hands[playerNum]->replaceCard(discard->takeDiscard());
  discard->discard(replaced_card); //put the replaced card in the discard pile
  cout << endl;
  cout << "Your new hand:" << endl;
  hands[playerNum]->print();
  // TODO: complete this function
}

//Draw deck is face down cards 
// Completed by Javier Laveaga
//deck is already set up from the beginning to accound for the cards 
// drawn by the players and in the discard pile (deck.draw())
void Game::drawFromDeck(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  } 
  Card *card_drawn = deck->draw();
  cout << "You drew:" << endl;
  cout << card_drawn->toString(); //prints the card
  cout << endl; //using cout here because toString returns a string.

  char answer; //keep prompting user until valid input is entered
  cout << "Would you like to keep this card? (y/n) ";
  cin >> answer;
  while(answer != 'y' && answer != 'n') {
    cout << "Would you like to keep this card? (y/n) ";
    cin >> answer;
  }
  cout << endl;
  if (answer == 'y') { //same as takeDiscard code except the argument 
    //same as takeDiscard code except the argument in replaceCard 
    //is the card that was drawn from the deck
    Card* replaced_card = hands[playerNum]->replaceCard(card_drawn);
    discard->discard(replaced_card); //put the replaced card in the discard pile
    cout << endl;
    cout << "Your new hand:" << endl;
    hands[playerNum]->print();
  } else if (answer == 'n') {
    cout << endl; // idk why the demo added this space but ok
    cout << "Your new hand:" << endl;
    hands[playerNum]->print();
    discard->discard(card_drawn); //put the card drawn from the deck into 
    //the discard pile
  }
}


bool Game::didPlayerWin(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }

  return hands[playerNum]->isWinningHand();
}
