// encrypt.cpp (Mmodified Javier Laveaga)
// Purpose: This program encrypts a user-provided word
//          using a 5-shift Caesar cipher.
// Written by: Megan Monroe (mmonroe)

#include <iostream>
#include <string>

using namespace std;

int main() {

  //Create two variables to hold the shift amount and the word to encrypt
  int shift_amount;
  string word_to_encrypt;

  //Print a message explaining the purpose of this program
  cout << "This program will encrypt a word provided by the user.";
  cout << endl;

  //Prompt the user for a word to encrypt
  cout << "Word to encrypt (in lowercase letters): ";
  //Retrive the word from the user and store it in our variable
  cin >> word_to_encrypt;
  cout << "What is the shift amount? ";
  cin >> shift_amount;

  //These variables store the length of the word and the position in that word
  //of the next letter to encrypt.
  int length_of_word = word_to_encrypt.length();
  int next_letter_pos = 0;

  cout << "Encrypted word: ";

  // Loop through each character of the word, generating the 
  // encrypted output as we go

//Shift that acomodates for all integers by taking the remainder. Aka figuring out net shift.
  int ShiftNew = shift_amount % 26;
  
  char shift_limit = 'z'- (ShiftNew-1); // the shift limit is the letter in the alphabet that corresponds to the
  //the given shift amount and that ensures proper wrapping around.
  while ( next_letter_pos < length_of_word ) {
    char new_letter;

    //Perform the shift; use a different equation to shift based on whether we
    //have to wrap-around to the start of the alphabet
    if ( word_to_encrypt[next_letter_pos] < shift_limit ) {
      new_letter = word_to_encrypt[next_letter_pos] + ShiftNew; //adding the shift if less than shift limit
    } 
    else {
      new_letter = word_to_encrypt[next_letter_pos] - 26 + ShiftNew; //wrapping around alphabet if greater than shift limt
    }

    //Print out the encrypted letter
    cout << new_letter;

    // Move to the next character
    next_letter_pos = next_letter_pos + 1;
  }

  //Finish off by printing a newline
  cout << endl;

  return 0;
} 
