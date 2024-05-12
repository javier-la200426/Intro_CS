#ifndef _DECK_H
#define _DECK_H

#include "card.h"
#include <string>

using namespace std;


class Deck {
public:
  const static int MAX_DECK_SIZE = 60;

  Deck(string deckFileName);
  ~Deck();

  bool  isEmpty();
  Card* draw();

private:
  int   topCard;
  Card* deck[MAX_DECK_SIZE];
};

#endif // _DECK_H
