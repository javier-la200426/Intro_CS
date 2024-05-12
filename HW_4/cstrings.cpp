/*
 * cstrings.cpp
 * Purpose: To read in lines from a file and determine, for each line, if any word
 * in the line is a proper substring of any other word in the line. (Hw04)
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

  int total_words = 0; ////number of words per line
  //for each line, find proper substrings
  char words[SIZE][SIZE];
  //total words saves the number of words per line
  total_words = read_line(infile, words); //Read the first line from the file
  //read a whole line (readline) store each word as one row in 2d array." 
  while (!infile.eof()) { //saving the words just like in example in read_line

    /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */

    int i = 0; 
    int j = 0; 
    //char current_char = words[i][j];
    char *haystack;
    char *needle;
    while (i < total_words) { //from row 0 to las row/word
      //current_char = words[i][j];
      haystack = &words[i][0]; //keep haystack constant temporarily
      while (j < total_words) { //iterates over rows/words again
        needle = &words[j][0]; //chang needle with a consant haystack
        char *substring = find_substring(haystack, needle);
        j++;
        //cout << current_char; 
        if (substring) { //if substring is found
          //cout <<  "substring found" << endl;
          //pring statements
          //loop over needle to print it
          int d = 0;
          char current_needle = needle[d];
          while (current_needle != '\0') { 
            cout << current_needle;
            d++;
            current_needle = needle[d];
          }

          cout << " is a substring of ";
          //loop over haystack to print it
          int e = 0;
          char current_haystack = haystack[e];
          while (current_haystack != '\0') { 
            cout << current_haystack;
            e++;
            current_haystack = haystack[e];
          }
          cout << endl; //allows for space between each line outputed
       } 
      }
      // cout << endl; //space betwen words
        
        j = 0;
        i++;
    }
    //cout << endl;

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
        char2 = *(word2+i);
        lower_char1 = tolower(char1); //changing characters to lower case
        lower_char2 = tolower(char2);
        if (lower_char1 != lower_char2) { //if they are not the same, then the words are not the same.
          equal = false;
          break; 
        }
        i++;
        char1 = *(word1+i); //more imporant
        char2 = *(word2+i);
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

  bool prefix = true;
  char char1 = *(word1); //first character of word1
  char char2 = *(word2); //first character of word2

  char lower_char1;
  char lower_char2;
  int  i = 0;
  while (char2 != '\0') {
    lower_char1 = tolower(char1); //changing characters to lower case
    lower_char2 = tolower(char2);
    //cout << lower_char1 << " " << lower_char2 << endl;
    if (lower_char2 != lower_char1) { //if they are not the same, then the words are not the same.
          prefix = false;
          break; 
        }

    i++;
    char2 = *(word2+i); //important that this one is after i++
    char1 = *(word1+i);
  }
return prefix;
  
}

/* find_substring
 * Arguments: two pointers to C-style strings
 * Description: determines whether string 'needle' is a proper substring of
 *              string 'haystack'. 
 * Return value: if 'needle' isn't a proper substring of 'haystack', return
 *               nullptr. Otherwise, return a pointer to the beginning of the
 *               first occurrence of 'needle' within 'haystack'.
 */
char *find_substring(char *haystack, char *needle) { // //return nullptr;
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */

   // char *haystack = &arr[0]; &arr[0] is what you put in function. 
  //*haystack and *needle are your pointers 

  bool same = is_equal(haystack, needle); // if words are the same, then they are not substrings
  if (same) {
    //cout << "same" << endl;
    return nullptr;
  }
  

  //initializing variables
  char char1 = *(haystack); //first character of haystack
  char char2 = *(needle);  //first character of needle

  //get length of needle
      int length1 = 0;
      int j = 0;
      while (char2 != '\0') { 
        length1++;
        j++;
        char2 = *(needle+j);
      }
      //cout << length1 << endl; // got 9 for "substring" = haystack

      //get length of haystack
      int length2 = 0;
      j = 0;
      while (char1 != '\0') { 
        length2++;
        j++;
        char1 = *(haystack+j);
      }

  int i = 0;
  char1 = (*(haystack)); //resetting character of haystack to the value at 0th index
  char2 = (*(needle)); // resetting character of needle to 0th index. 
  char arr[100] = {'\0'}; //creating temporary array of characters to stor temporary string
  char *new_string = &arr[0];
  char new_string_char = *(new_string);//retrieves value of array at index 0
  bool past_limit = false;
  bool equality = false;
  char *pointer; //this is what function will return
  //loop through haystack
  while (char1 != '\0') { 
        if ((char1 == char2)) {
          pointer = &haystack[i]; //updates pointer to be pointing to ith ith index in hastack
          //creating new temporary string
          
          int l = 0;
          for (int k = i; k < (i + length1); k++ ) { //i is index of haystack where char1 = char2
            //k just goes from i to length of the needle. 
            //l is just going from 0 to length of the needle to make new string
            //cout << i << " " << k << " " << l << endl;
              *(new_string+l) = *(haystack + k); //left side is going from index 0 to length of needle  to make new string
              //right side is going from current index i to length of needle.
              new_string_char = *(new_string+l); //creating new string to store temporariliy 
              if ((new_string_char == '\0')) { //if we have reached end of haystack before completing loop
              //(aka before obtaining a proper new string equal in length to needle)
                past_limit = true; //needle is not substring
                break; //break out of for loop
              }
              //cout << new_string_char << endl; //this one
              l++;  
          }
          
        //  cout << "su";
        //nope
         if (past_limit) { //if we go past haystack before obtainign a proper new string equal to needle
            return nullptr; //then needle is not substring
            break; //also break out of while loop
          }
          
          //compares new string with the needle to see if they are equal 
          equality = is_equal(&arr[0], &needle[0]); //comparing needle to new array
          
          if (equality) { //if the temporary array is equal to needle, you have a substring
            //cout << "Yay substrings";
           // cout << endl;
           return pointer;
           break; //break out of while loop (no need to check more)
          } else { //reset new temporary array to an 'empty' array to reuse it for the next iteration
            for (int h=0; h<100; h++) { 
             arr[h] = '\0'; 
            }
          }
          //nope
        }
        i++;
        char1 = tolower(*(haystack+i));
    }
  return nullptr; //incase that no of the letters match, 
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
