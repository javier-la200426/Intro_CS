/*
 * Javcstring.cpp
 * Purpose: To complete the is_equal function (lab04)
 * Submitted by: {Javier Laveaga AND jlavea01}
 */


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cctype> //Lets us use the isalpha function

using namespace std;

const int SIZE = 50;
int read_line(ifstream &infile, char words[SIZE][SIZE]); //number of words in each line
bool is_equal(char *word1, char *word2);
bool is_prefix(char *word1, char *word2);
char *find_substring(char *haystack, char *needle);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "ERROR: A filename must be specified as the first argument.\n";
    exit(EXIT_FAILURE);
  }

  /* Open the file */
  ifstream infile;
  infile.open(argv[1]); 

  /* Error check */
  if (infile.fail()) {
    cerr << "ERROR: Error opening file - ";
    cerr << "please check that you specified the correct file name\n";
    exit(EXIT_FAILURE);
  }

  /*
  //Jav is equal testing
    char word1[] = "Foursee";
    char word2[] = "FouhsEe";

    bool equality = is_equal(&word1[0], &word2[0]);
    if (equality) {
      cout << "equal" << endl;
    } else {
      cout << "not equal" << endl;
    }
  //Jav
  */

  int total_words = 0; ////number of words per line
  //for each line, find proper substrings
  char words[SIZE][SIZE];
  total_words = read_line(infile, words); //Read the first line from the file
  //read a whole line (readline) store each word as one row in 2d array." 
  while (!infile.eof()) { //saving the words just like in example in read_line


 


    /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */
    /* YOUR CODE GOES HERE */
    /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */





    total_words = read_line(infile, words); //Read the next line from the file
  }
  

  /* Close the file */
  infile.close();

  return 0;
}

/* is_equal
 * Arguments: two pointers to C-style strings
 * Description: determines if two C-style strings are equivalent
 * Return value: true if strings are equivalent, false otherwise
 */
bool is_equal(char *word1, char *word2) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
  
  // char *word1 = &arr[0]; &arr[0] is what you put in function. 
  //*word1 and *word2 are your pointers 

  char char1 = *(word1); //char1 = a given individual character in word1
  char char2 = *(word2); //char2 = a given individual character in word2

  //counting number of letters in word1
  int count1 = 0;
  int i = 0;
  while (char1 != '\0') { //loop untill you see this
    count1++;
    i++;
    char1 = *(word1+i);
  }
  //counting number of letters in word2
  int count2 = 0;
  i = 0;
  while (char2 != '\0') {
    count2++;
    i++;
    char2 = *(word2+i);
  }
 // cout << count1 << " " << count2 << endl;

  bool equal = true;
  if (count1 != count2) { //if the words are not the same length, then they are not equal
    equal = false;
  } else { // if they are the same length, then check that every letter is equal
    char1 = *(word1); 
    char2 = *(word2);
    i = 0;
    char lower_char1;
    char lower_char2;
    while (char1 != '\0') { //loops through every character in both words and compares them
        char1 = *(word1+i);
        char2 = *(word2+i);
        lower_char1 = tolower(char1); //changing characters to lower case
        lower_char2 = tolower(char2);
        //cout << lower_char1;
       // cout << char2 << endl;
        if (lower_char1 != lower_char2) { //if they are not the same, then the words are not the same.
          equal = false;
          break; 
        }
        i++;
        char1 = *(word1+i);
    }
  }
  return equal;
}

/* is_prefix
 * Arguments: two pointers to C-style strings
 * Description: determines if string word2 is a prefix of string word1
 * Return value: true if word2 is a prefix of word1, false otherwise
 */
bool is_prefix(char *word1, char *word2) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
  return false;
}

/* find_substring
 * Arguments: two pointers to C-style strings
 * Description: determines whether string 'needle' is a proper substring of
 *              string 'haystack'. 
 * Return value: if 'needle' isn't a proper substring of 'haystack', return
 *               nullptr. Otherwise, return a pointer to the beginning of the
 *               first occurrence of 'needle' within 'haystack'.
 */
char *find_substring(char *haystack, char *needle) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
  return nullptr;
}

/* Retrieve a line of input from a file, parse it into individual words, and
 * store those words in the "words_in_sentence" 2D-array. Each "row" of
 * words_in_sentence is another word. Return the total number of words read in.
 *
 * For example, if we read in the sentence "Here I am!", then the
 * first 3 rows (R) and first 5 columns (C) of the words_in_sentence array 
 * will look like the picture belwo (the empty cells hold garbage values):
 *
 *        C0   C1   C2   C3   C4
 * R0:  | H  | e  | r  | e  | \0 | 
 * R1:  | I  | \0 |    |    |    | 
 * R2:  | a  | m  | \0 |    |    | 
 *
 * NOTE: We have to write "ifstream &infile" as a parameter to pass an input
 * file stream correctly to a function. If you need to write a function that
 * takes a file stream as an argument, always put the '&' in front of the name
 * of your file stream.
 */
int read_line(ifstream &infile, char words_in_sentence[SIZE][SIZE]) {
  int spot = 0;
  int word_index = 0;
  char *next_word;
  char next_char;

  infile.get(next_char); // jav:getting character by character no matter if it is white space
  while (!infile.eof() && next_char != '\n') {
    next_word = words_in_sentence[word_index]; // gives pointer the memory address of the first element of w
    //words in sentence arrray. 

    //Written question 1 asks about this loop
    while (!infile.eof() && isalpha(next_char)) { //it stores one one word in a row. 
      next_word[spot] = next_char; //Written question 2 asks about this line
      ++spot;
      infile.get(next_char);  
    }
    //Bellow is what while loop is doing
    /*
           C0   C1   C2   C3   C4
 * R0:  | H  | e  | r  | e  
 * R1:  
 * R2:  
    */

    if (spot > 0) {
      next_word[spot] = '\0';
      ++word_index;
      spot = 0;
    } else {
      infile.get(next_char);
    }
  }
  return word_index;
}
