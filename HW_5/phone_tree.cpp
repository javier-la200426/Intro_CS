// phone_tree.cpp
// Purpose: To read in a proposed phone tree and determine whether or not the call plan can be used
// to reach every parent. If it can, it will tell the principal who to call first and how long it 
// will take for every parent to be called. If it can't, it will curse the Harold Hacker.
// Written by: {Javier Laveaga AND jlavea01}

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Call_plan {
    //Usha 5 Kurt. Usha would be parent1, 5 would be the number of seconds, and Kurt is parent2. 
    string parent_1;
    string parent_2;
    int sec;
};

Call_plan *read_tree(string filename, int *plan_size);
void print_tree(Call_plan *plan, int plan_size);
bool first_rule(Call_plan *plan, int plan_size, int *alone_par1_p);
int count_sec(Call_plan *plan, int plan_size, int alone_par1);


int main(int argc, char *argv[]){
    //Make sure I was actually given a filename on the command-line
    if (argc < 2) {
        cerr << "ERROR: Expecting a file name as a command-line argument.";
        cerr << endl;
        exit(EXIT_FAILURE);
    }
    //Read in tree into struct and print it 
    int plan_size;
    Call_plan *plan = read_tree(argv[1], &plan_size);
    //print_tree(plan, plan_size);

    //Determine if it passes the first rule [if it does then the pointer will point to the parent the 
    //principal will call (aka the parent that is alone)]
    int alone_par1; //initialize index of the name that is alone. 
    //after line below, the alone_par1 should contain the proper index
    bool First_rule_passed = first_rule(plan, plan_size, &alone_par1); 
    if (!First_rule_passed) {
        cout << "Curse you, Harold Hacker!" << endl;
    } else {
        string principal_parent = plan[alone_par1].parent_1;
        //cout << principal_parent << endl; //prints out name of first parent to call
        int sum_sec = count_sec(plan, plan_size, alone_par1);
        cout << "Starting with " << principal_parent << 
        " the phone tree will succeed in " << sum_sec << " seconds!" 
        << endl;
    }

    delete [] plan;

    return 0;
} 

/*
 * Description: This function reads the proposed phone tree
 *              into an array of call Plan structs
 * Input: The name of the file to read from, and the address of the
 *        integer that will store the total size of the plan.
 * Output: A pointer to the finished array of Call_plan structs
 */
Call_plan *read_tree(string filename, int *plan_size) { 
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << " ERROR: Problem opening the file." << endl;
        exit(EXIT_FAILURE);
    }
    
    int first_num; 
    infile >> first_num;
    *plan_size = first_num; //size is equal to first character read
    Call_plan *call_plan_p = new Call_plan[*plan_size]; //create pointer to new array of call plan structs
    
    for (int i = 0; i < *plan_size; i++) { //fill up the array of call plan stucts
        infile >> call_plan_p[i].parent_1 >> call_plan_p[i].sec >> call_plan_p[i].parent_2;
    }

    infile.close();
    return call_plan_p;
}

/*
 * Description: This function prints out the contents of the phone tree stored in the array of 
 * Call_plan structs. 
 * Input: The pointer to the array of Call_plan structs and its size or number of parents/lines. 
 * Output: prints out the contents of the array of Call_plan structs.
 */
void print_tree(Call_plan *plan, int plan_size) {
    cout << endl;
    for (int i = 0; i < plan_size; i++) {
        cout << plan[i].parent_1 << " "
             << plan[i].sec << " "
             << plan[i].parent_2 << endl;
    }
    cout << endl;
}

/*
 * Description: This function determines whether or not there is a maximum of 1 parent on the 
 * left that does not repeat itself on the right. In other words, it determines if the given plan
 * passes rule number1 (A maximum of 1 parent on the left is allowed to not have a pair on the other side). 
 * Input: A pointer to the finished array of Call_plan structs, the size of the plan (# of parents), 
 * and the address of an integer where the unpaired parent Call_plan index will be stored. 
 * This parent is supposed to be called by the principal. 
 * Output: Returns a boolean indicating whether or not it has passed the first rule. 
 */
bool first_rule(Call_plan *plan, int plan_size, int *alone_par1) {

    //This function determines whether or not it has passed the first rule. 
    //A maximum of 1 parent on the left is allowed to not have a pair on the other side.

    //Initializing variables
    string Parent_1;
    string Parent_2;
    bool passed = true;
    int unpaired_count = 0;
    for (int i = 0; i < plan_size; i++) { //iterate over the parents on the left
        Parent_1 = plan[i].parent_1;
        for (int j = 0; j < plan_size; j++) { //iterate over the parents on the right
            Parent_2 = plan[j].parent_2;
            if (Parent_1 == Parent_2) { //if you find a pair, then move on to next parent1
                break;
            } else if (j == plan_size - 1) { //if you get to end of parent2, and you have not
            //executed break (aka find a pair)
                unpaired_count++; //that means that parent1 is not repeated on the right
                *alone_par1 = i; //this is the index of the lone parent who needs to be called
                //by the principal
            }
        }
    }
    if (unpaired_count > 1) { //if true, that means that the phone tree is invalid
        passed = false;
    }
    return passed;
}

/*
 * Description: Counts the number of seconds it will take
 * for every parent to be called by starting from the parent called by the principal.
 * Goes parent by parent in order (sees where each parent on the right is located on the left)
 * Input: Takes in a pointer to the finished array of Call_plan structs, the size of the plan 
 * (# of parents), and the index that stores the parent that should be called by the principal.
 * Output: the seconds that it will take all of the parents to be called. 
 */
int count_sec(Call_plan *plan, int plan_size, int alone_par1) {

        // function counts number of seconds by starting from the principal parent 
        // and going parent by parent in order (sees where each parent on the right is located on the left).
        int First_second = plan[alone_par1].sec; //seconds that first parent takes to call the next one
        int sum_sec = First_second;

        int count = 0; //counts the number of matches between left and right side names
        string right_names = plan[alone_par1].parent_2; //begin with parent next to principal parent
        int i = 0;
        while (i < plan_size) {
            //if the parent2 of principal parent is equal to one of the parent1's, then
            if (right_names == plan[i].parent_1) { 
                sum_sec = sum_sec + plan[i].sec; //adding to sum 
                right_names = plan[i].parent_2; //update right_names (names on the right after matching)
                count ++;
                if (count == plan_size -2) {//-1 b/c of the pattern that u only need parents-1 calls needed 
        //and another -1 b/c you already sum the first principal parent before loop
                    break; //break out of for loop
                }
                i = 0; //so that it starts checking from beginning for next right_name comparison
                continue; //so that it does not add 1 to i.
            }
            i++;
        }
       return sum_sec;
}