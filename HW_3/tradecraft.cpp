/*
 * tradecraft.cpp
 * Purpose: To read in a file containing a Caesar-encrypted text and output the shift amount that 
 * was used to encrypt it. 
 *  {Javier Laveaga AND jlavea01}
 * */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//function declarations
void count_letter(string filename, int Letters[]);
string text_string_converter(string filename);
void shift_amount(int LetterCounts[]);
int edge_num_single_letters(string StringText);
int edge_num_letters(int LetterCounts[]);
string edge_single_letters(string StringText);
void edge_shift_amount(int LetterCounts[]);

int main(int argc, char *argv[]) {

    //checking that there are at least two arguments
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }

    //Convert Text to a String
    string StringText = text_string_converter(string (argv[1]));
  
    int LetterCounts [26]; //array is declared here (does not hold any values)

    // Count how many times each letter in the alphabet repeats
    count_letter(StringText,LetterCounts); // calling function to modify array and put in count numbers
    //This works because of pass by reference

    //Count number of letters
    int num_of_letters = edge_num_letters(LetterCounts);

    //Count number of single letters
    int Num_Single_Letter = edge_num_single_letters(StringText);

    //do edge case method (most frequent single letter = 'a'), if text contains
    //less than 400 letters and the number of single letters is greater than 2
    if ((num_of_letters <400) &&  (Num_Single_Letter > 2)) { 

        string single_letters = edge_single_letters(StringText); //get all single letters
        int SingleLetterCounts [26] = {0}; // create an array that will hold counts of single letters
        count_letter(single_letters,SingleLetterCounts); // modify array with counts of single letters

        //Determine maximum count in array and calculate shift amount based on that. (based on 'a' = most repeated single letter)
        edge_shift_amount(SingleLetterCounts);
        
    } else { // do the regular way (finding most frequent letter which equals 'e')
    
        //Determine maximum count in array and calculate shift amount based on that. (frequency base (letter e))
        shift_amount(LetterCounts);
    }
}

/* text_string_converter
 * Input: A filename with text (.in file format).
 * Description: Opens a file with text and coverts it into a string.
 * Output: A string with the text contained in the file.
 */ 
string text_string_converter(string filename){
    //OPENING the file
    ifstream infile;
    infile.open(filename); 

    /* Error check */
    if (!infile.is_open())
    {
        cerr << "ERROR: Error opening file - ";
        cerr << "please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }

    char next_char;
    string StringText = ""; 
    //putting file into a string
    infile.get(next_char); //read next character once before loop
     while(!(infile.eof())) {
        StringText = StringText + next_char; //keep adding characters 
        infile.get(next_char);

     }
    infile.close();
    return StringText;
}

/* count_letter
 * Input: a string containing the text and the array in which the counts will
 * be stored.
 * Description: Counts the number of times each letter in the alphabet is present in a string and
 * puts the counts of each letter into an array in alphabetical order. 
 * Output: The modified array contating the counts for each letter. 
 */
void count_letter(string StringText, int LetterCounts[]) { //the array is empty in every index

    //COUNTING process starts:

    char lowercase_letter = 'a'; //start at 'a' so that array count-values are in alphabetical order
    char uppercase_letter = 'A';
    for (int j = 0; j < 26; j++) {
        char current; //curren character
        int countLetter = 0; //counts  how many times the letter appears
        int LengthText = StringText.length(); //gets length of Text
            for (int i = 0; i < LengthText; i++) { //i is each character in string
                current = StringText[i]; 
                if ((current == lowercase_letter)|| (current == uppercase_letter)) { //if the letter shows up either in 
                //lowercase or upercase
                    countLetter++; //up the count by one
                }
            }
        LetterCounts[j] = countLetter;//adds the count of current letter into array
        lowercase_letter = lowercase_letter + 1; //moves on to the next letter in alphabet one by one
        uppercase_letter = uppercase_letter + 1; //same as above but for uppercase letters
    }
       // cout << countLetter;
}

/* shift_amount
 * Input: Takes in an array holding integers which represent the counts of each letter in the alphabet.
 * Description: Takes in the array and gets index of the max count, which corresponds to a letter
 * in the alphabet. Then it calculates the shift amount based on the index of the max count.
 * Output: outputs the shift amount to the screen.
 */
void shift_amount(int LetterCounts[]) {

//function starts here (function would take in array with counts and outputs index of max count, which
   // corresponds to a letter in alphabet)
    int MaxCount = 0;
    int MaxCountIndex;
    //Iterates over array with counts and determines the highest count
    for (int i = 0; i < 26; i++) {

        int currentCount = LetterCounts[i]; //current count is in ith index
        if (currentCount > MaxCount) { //if the current value is greater than max count

            MaxCount = currentCount; //update max count to be the current value
            MaxCountIndex = i; // save the index of the highest/max count
        }
    }

    //Determining Shift Amount
    int ShiftAmount = MaxCountIndex - 4; //-4 because e has index of 4. 
    if (ShiftAmount < 0){ // if the shift amount is negative, that means that letter is behind e. 
        ShiftAmount = ShiftAmount + 26; // thus you need to loop around alphabet to get correct shift amount
    }
    cout << "The shift amount is: " << ShiftAmount << endl;
    
    //The following helped to visualize the ShiftAmount calculations:

    //Create an array with all the letters of alphabet
    //This does not help with the actual calculations of shift amount but it helps 
    //visualize how the shift amount calculations need to be done given a MaxCountIndex
    //which corresponds to the index of a letter in alphabet:
    /*
    char letter = 'a'; // first letter in alphabet
    char Alphabet_array [26];
    for (int j = 0; j < 26; j++) {
        Alphabet_array[j] = letter;
        letter = letter + 1;
    }
    cout << Alphabet_array[MaxCountIndex] << endl; //Gives the letter that e is equal to 
    */
}

/* edge_num_single_letters
 * Input: Takes in a string with text.
 * Description: It goes through every character and determines the number of single letters in the text.
 * Output: an integer that represents the number of single letters.
 */
int edge_num_single_letters(string StringText) {
    
    int Num_Single_Letter = 0;
    
    //for special cases:
    //If single letter is first in the string. ex:a(space)
    if((StringText[0] != '"') && (StringText[0] != ' ') && (StringText[1] == ' ')) {
        Num_Single_Letter++;
    }

    //If single letter is last in string. ex: (space)a
    int last_Index = StringText.length() - 1;
    if((StringText[last_Index] != '"') && (StringText[last_Index] != ' ') && (StringText[last_Index-1] == ' ')) {
        Num_Single_Letter++; 
    }

    //count single letters. Ex: (space)a(space)
    char current; //curren character
    int LengthText = StringText.length(); //gets length of Text 
    char BeforeBefore; //the character two positions down to left
    char Before; //the character right to the left
    for (int i = 2; i < LengthText; i++) {

        current = StringText[i];  
        BeforeBefore = StringText[i-2];
        Before = StringText[i-1];
        if ((current == ' ') && (BeforeBefore == ' ') && (Before != ' ')) { //if current character is
            //a space, and the character before is a letter (aka not a space), and the character
            // before that (beforebefore) is a space, then the current character is a single letter
            Num_Single_Letter++;
            //Before = single letter
        }
    }
    return Num_Single_Letter;

} 

/* edge_single_letters
 * Input: Takes in a string with text.
 * Description: It goes through every character in the text and puts all the single letters one next to 
 * the other into a new string. (Almos the same as edge_num_single_letters except for the output).
 * Output: a string containing all the single letters next to each other.
 */
string edge_single_letters(string StringText) {
    //****stores single letters:
    string single_letters = "";
    //for special cases
    //If single letter is first in the string. ex:a(space)
    if((StringText[0] != '"') && (StringText[0] != ' ') && (StringText[1] == ' ')) {
        single_letters = single_letters + StringText[0];
    }
    //If single letter is last in string. ex: (space)a
    int last_Index = StringText.length() - 1;
    if((StringText[last_Index] != '"') && (StringText[last_Index] != ' ') && (StringText[last_Index-1] == ' ')) {
        single_letters = single_letters + StringText[last_Index];
    }

    //store single letters. (space)a(space)
    char current; //curren character
    int LengthText = StringText.length(); //gets length of Text 
    char BeforeBefore; //the character two positions down to left
    char Before; //the character right to the left
    for (int i = 2; i < LengthText; i++) {
        current = StringText[i];  
        BeforeBefore = StringText[i-2];
        Before = StringText[i-1];

        //if current character is a space, and the character before is a letter (aka not a space),
        //and the character before that (beforebefore) is a space, then the current character is a 
        //single letter. Before = single letter
        if ((current == ' ') && (BeforeBefore == ' ') && (Before != ' ')) {
            single_letters = single_letters + Before; // string containing all single letters. 
        }
    }
    return single_letters;
} 

/* edge_shift_amount
 * Input: Takes in an array holding integers which represent the counts of each letter in the alphabet.
 * Description: Takes in the array and gets the index of the max count, which corresponds to a letter
 * in the alphabet. Then it calculates the shift amount based on the index of the max count.
 * (This is the same as the shift_amount function except now it assumes that letter with the highest count is 'a').
 * Output: outputs the shift amount to the screen.
 */
void edge_shift_amount(int LetterCounts[]) {

    int MaxCount = 0;
    int MaxCountIndex;
    //Iterates over array with counts and determines the highest count
    for (int i = 0; i < 26; i++) {

        int currentCount = LetterCounts[i]; //current count is in ith index
        if (currentCount > MaxCount) { //if the current value is greater than max count

            MaxCount = currentCount; //update max count to be the current value
            MaxCountIndex = i; // save the index of the highest/max count
        }
    }

    //Determining Shift Amount
    int ShiftAmount = MaxCountIndex; // -0 technically because 'a' has index 0. 
    cout << "The shift amount is: " << ShiftAmount << endl;

}

/* edge_num_letters
 * Input: Takes in an array holding the counts of each letter in the alphabet in a text. 
 * Description: Takes an array with counts and returns the sum of all the counts, which represents
 * the number of letters in the text. 
 * Output: outputs an integer representing the amount of letters in a text. 
 */
int edge_num_letters(int LetterCounts[]) {

    int sum = 0;
    for (int i = 0; i < 26; i++) {
        sum = sum + LetterCounts[i];
    }
    return sum;
} 
