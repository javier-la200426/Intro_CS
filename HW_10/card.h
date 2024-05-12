#ifndef _CARD_H
#define _CARD_H

#include <string>

using namespace std;


class Card {
public:
  Card(int cardNumber);

  int getNum();
  //returns a string so be sure to save it, then print
  // or print it directly using cout <<
  string toString(); //prints the card 


  string getTopEdge();
  string getBlankLine();
  string getNumberLine();
  string getBottomEdge();

private:
  int cardNum;
};

#endif // _CARD_H
