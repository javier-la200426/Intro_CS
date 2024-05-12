
/*
 * top3.cpp
 * Purpose: To read in a file with a list of positive numbers from a file containing at least 3 
 * and outmost 25 numbers and output the top 
 * three numbers in sorted order, highest to lowest.  {Javier Laveaga AND jlavea01}
 * */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
//checking that there are at least two arguments
 if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }
    //opening the file
    ifstream infile;
    infile.open(argv[1]); 

    /* Error check */
    if (!infile.is_open())
    {
        cerr << "ERROR: Error opening file - ";
        cerr << "please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }

    //Intializing for while loop
    //creating an array of size 25 filled with 0's (since every positive number is >=0)
    int Numbers[25] = {0};
    int next_char; 
    int count = 0; //count that will change index of array

    infile >> next_char; //read next character once before loop

    //Reading until end of file and puttign all integers into an array
    while(!(infile.eof())) { 
        Numbers[count] = next_char;

        infile >> next_char;
        //read another charcter before end of while loop
        count ++;  
    }
    infile.close();
    
    //Initializing variables used in for loop.
    //Setting everything equal to 0 since it is assumed that every number will 
    //be positive, so that means that 0 will be less than or equal to every number provided
    int First = 0;
    int Second = 0;
    int Third = 0;
    int PastFirst = 0;
    int PastSecond = 0;
    
    //Loop that iterates over every number in list provided that max length is 25 numbers
    for (int i = 0; i < 26; i++) {
        int CurrentNum = Numbers[i]; //Current number is an integer in index i of Number array 
        //in a given iteration
        if (CurrentNum > First){ //if current value is greater than First value then:
            PastFirst = First; // saving old value in First position
            First = CurrentNum; //makes the current value value first

            PastSecond = Second; //saving old value in Second position
            Second = PastFirst; //make what used to be 1st 2nd
            Third = PastSecond; //make what used to be second 2nd 3rd. 
            
        } else if(CurrentNum > Second) { //if current value is greater than second position value
            PastSecond = Second; //saving old value in Second position
            Second = CurrentNum; //make current value second position
            Third = PastSecond; //make what used to be second 3rd. 
            
        } else if(CurrentNum > Third){ //If current value is greater than 3rd
             Third = CurrentNum; //simply just make current 3rd without domino effect taking place
        }
        
    }
    // Print First, Second, and Third numbers each in an new line
    cout << First << endl;
    cout << Second << endl;
    cout << Third << endl;
    

}
