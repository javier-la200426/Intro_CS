// hw1_palindrome.cpp
// Purpose: This program asks for a word and determines if it is a palindrome, 
//close enough to a palindrome, or not a palindrome. It prompts the user to enter another word if 
// it is a palindrome or close enough.
// Written by: Javier Laveaga jlavea01


#include <iostream>
#include <string>


using namespace std;

int main()
{

    bool palindrome = true;
    cout << "Greetings! I am the palindrome decider!" << endl; //only executes once
    while(palindrome == true) { //putting in a while loop as long as user enters a palindrome 
        
        cout << "Please enter a word: ";
        string word;
        cin >> word;
      
        //saving length of word
        int length_word = word.length();
        
        //palindrome
        int j = 0;
        string reverse_word;

        //loop creates reverse word
        //i starts at last index of word and then goes to first index (0)
        //j goes from 0 to length of word -1 to fill out palindrome or reverse_word. 
        for (int i = (length_word -1); i!= -1; i--) { 
            reverse_word = reverse_word + word[i];
            j++;
        }
        //Determining close enough palindrome
        
        //Getting First thre characters of inputed word.
        string FirstThreeWord;
        for (int i = 0; i < 3; i++) {
            FirstThreeWord = FirstThreeWord + word[i];
        }
            
        //Getting First three characters of reversed word.
        string FirstThreeReverse;
        for (int i = 0; i < 3; i++) {
            FirstThreeReverse = FirstThreeReverse + reverse_word[i];
        }

        //Displaying
        if (word == reverse_word) { //if palindrome
            cout << "Your word is a palindrome! Fantastic!" << endl;
        } else if( FirstThreeWord == FirstThreeReverse) { //if close enough palindrome
            cout << "Not quite a palindrome, but close enough." << endl;
        
        } else {
            cout << "Your word is NOT a palindrome. Thanks anyway!" << endl;
            palindrome = false;
        }

    }     

}