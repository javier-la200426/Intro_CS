/*
 * mutations.cpp
 * Purpose: to read in a data file with mutation data 
 * inputed by user, read the file into the struct created, and 
 * perform the queries necessary chosen by the user.
 *  {Javier Laveaga AND jlavea01}
 * */

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Gene {
    string g_name;
    string arr_mutated_genes [5];
    int array_costs [5];
};

//Function declarations
void opening_file(int *num_unique_genes, ifstream *infile, string *filename);
Gene *read_genes(int num_unique_genes, ifstream *infile, string filename);
void populate_names (Gene *genes_array, int num_unique_genes, ifstream *infile);
void read_mut_genes_and_cost (Gene *genes_array, int num_unique_genes, string filename);
void initialize_mut_genes_and_cost (Gene *genes_array, int num_unique_genes);
void find_empty_spot_mgene_cost (Gene *current_gene, string mutated_g, int cost );
void print_gene_data_check (Gene *genes_array, int num_unique_genes);
void print_data_query (Gene *genes_array, int num_unique_genes);
bool possible_mutation_query (Gene *genes_array, int num_unique_genes, 
    string source_gene, string target_gene, int *gene_index, int *index_cost);
bool possible_mutation_energy_query (Gene *genes_array, int gene_index, 
                                    int index_cost, int user_energy);

// Hard coded queries that the user can execute
const string PRINT_DATA = "p";
const string MUTATION_POSSIBLE = "m";
const string MUTATION_WITH_ENERGY = "me";
const string QUIT = "q";

int main() {

    string filename;
    int num_unique_genes = 0;
    ifstream infile;
    //open file and save number of genes as well as the filename
    opening_file(&num_unique_genes, &infile, &filename);
    // cout << num_unique_genes << endl;
    //Read file into data structure
    Gene *genes_array = read_genes(num_unique_genes, &infile, filename);
    //print_gene_data_check (genes_array, num_unique_genes);
   
    // Perform the loop of requesting and executing queries
    cin.ignore(); //ignore the \n character that remains (caused by 
    //opening the asking for a filename in opening_file function above).
    string line_in; //line inputed
    string query;
    cout << "Enter a query: "; 
    

    stringstream sstream;
    
    while (getline(cin, line_in)) { //will keep asking the user for input. Returns false 
        //cin.ignore(); //ignores the \n that the >> thing did not read in * this line.
    //ignore funtction ignore the next thing (not necessarily whole line
    sstream.str(line_in);
    sstream >> query; //first part of the line
        if (query == PRINT_DATA) {
            print_data_query (genes_array, num_unique_genes);

        } else if (query == MUTATION_POSSIBLE) {
            //string after_query;
            //getline(infile, after_query);
            // cout << query << endl; // prints "m"
            bool possible;
            string source_gene, target_gene;
            sstream >> source_gene;
            sstream >> target_gene;
            //cout << source_gene << " " << target_gene;
            int gene_index = 0; //for 'me' query (useless here)
            int index_cost = 0; //for 'me' query (useless here)
            possible = possible_mutation_query (genes_array, num_unique_genes, 
                    source_gene, target_gene, &gene_index, &index_cost);
            if (possible) {
                cout << source_gene << " can mutate into " << target_gene;
                cout << endl;
            } else {
                cout << source_gene << " cannot mutate into " << target_gene;
                cout << endl;
            }
            
        } else if (query == MUTATION_WITH_ENERGY) {
            bool possible_1; //possible w/out taking into account energy
            string source_gene, target_gene;
            sstream >> source_gene;
            sstream >> target_gene;

            int gene_index = 0; // index where inputed unique gene
            // is located in array
            int index_cost = 0; //stores where the inputed mutated gene by user
            // is in the array of mutated genes of 1 unique gene (the one inputed by user)
            possible_1 = possible_mutation_query (genes_array, num_unique_genes, 
                            source_gene, target_gene, &gene_index, &index_cost);
            //pass first check
            if (!possible_1) { //if false (can't mutate)
                cout << source_gene << " cannot mutate into " << target_gene;
                cout << endl;
                //cout << index_cost << endl; //is 0 b/c there was never 
                // a match b/t the target gene and a mutated gene stored
                // so prints out initialized value =0

                //cout << check1_index; //0 here cause it never found match
                //b/t user input and gene in array

            } else { //if it can mutate, do energy calculations
                //read in the integer inputted
                int user_energy = 0;
                sstream >> user_energy;
                //Function starts here
                //cout << gene_index; // works
                //cout << index_cost << endl; //works
                bool possible_2; //represents possible mutation with energy
                possible_2 = possible_mutation_energy_query (genes_array, gene_index, 
                                                    index_cost, user_energy);
                if (possible_2) {
                    cout << source_gene << " can mutate into " << target_gene
                    << " with evolutionary cost " << user_energy << endl;
                    //[Source] can mutate into [Target] with evolutionary cost [Energy]
                } else {
                    cout << source_gene << " can mutate into " << target_gene
                    << " but not with evolutionary cost " << user_energy << endl;
                }
            }

        } else if (query == QUIT) { //this is how you get out of while loop. 
            delete [] genes_array;
            return 0; // this exits the program, the main program
        } else {
            cout << query << " not recognized." << endl;                             
        }
        cout << endl << "Enter a query: ";
        sstream.clear(); //very important
        
    }

    //these are not really needed. Just in case.
    delete [] genes_array;
    return 0;
}

/* opening_file
 * Input: A pointer to the number of unique genes, a pointer to a file stream
 * variable, and a pointer to a filename.
 * Description: Prompts the user for a filename, says if there was an error
 * opening the file, and reads the number of unique genes.
 * Output: Prints out commands asking for user input as well as errors. 
 * Secretly returns the number of unique genes and the filename.
 */ 
void opening_file(int *num_unique_genes, ifstream *infile, string *filename) {
    cout << "Enter data file name: ";
    cin >> *filename;
    (*infile).open(*filename);  //open file
    if (!(*infile).is_open()) { //if error opening file
        cerr << "ERROR OPENING FILE: Exiting Program" << endl;
        exit(EXIT_FAILURE); //ask if it is ok to have it here
    }
    (*infile) >> *num_unique_genes; //save first number to number of unique genes
    (*infile).ignore(); //ignore the \n character
}

/* read_genes
 * Input: the number of unique genes, a pointer to a file stream variable, and
 * and the file requested by the user.
 * Description: Reads in the gene data from the file into an array of genes.
 * Output: A pointer to a an array of unique genes.
 */ 
Gene *read_genes(int num_unique_genes, ifstream *infile, string filename) {
    Gene *genes_array = new Gene[num_unique_genes]; // allocate a new genearray
   //read and populate the names of the genes
    populate_names (genes_array, num_unique_genes, infile);
    //initialize the genes and cost to known values
    initialize_mut_genes_and_cost (genes_array, num_unique_genes);
    //reads and populate the mutated genes and cost  
    read_mut_genes_and_cost (genes_array, num_unique_genes, filename);
    
    return genes_array ;
}

/* populate_names
 * Input: a pointer to an array of genes, the number of unique genes, and 
 * a pointer to a file stream variable.
 * Description: Reads in the names of the genes in the file and stores them 
 * in the array of genes.
 * Output: Secretly gives a name-populated array of genes.
 */ 
void populate_names (Gene *genes_array, int num_unique_genes, ifstream *infile) {
    string name;
    stringstream sstream;
    string line;
    for (int i = 0; i < num_unique_genes; i++)  { //loops over genes
        getline(*infile,line); 
        sstream.str(line); //load up stream with the current line
        sstream >> name; //save the first string to name
        sstream.clear();
        genes_array[i].g_name = name; //save the gene name for the ith gene
    }
    (*infile).close();
}

//reads and populates (to gene array) the mutated genes and cost 

/* read_mut_genes_and_cost
 * Input: a pointer to an array of genes, the number of unique genes, and 
 * a pointer to a file stream variable.
 * Description: Reads a file and stores the mutated genes and the cost associated
 * with them in the array of genes.
 * Output: Secretly gives an array of genes whose costs and mutated genes are filled.
 */ 
void read_mut_genes_and_cost (Gene *genes_array, int num_unique_genes, string filename) {
    ifstream infile;
    (infile).open(filename);
    stringstream sstream;
    //line is the current line, name is the name of the unique gene, and 
    //mutated_g is mutated gene
    string line, name, mutated_g;
    int cost; //that is current cost
    getline(infile,line); //go past the number of unique genes on the top
     for (int i = 0; i < num_unique_genes; i++)  { //iterates over each line
        getline(infile,line); 
        sstream.str(line); //load current line into stream
        Gene *current_gene = &(genes_array[i]); //save address of current gene
        sstream >> name; //go past the name
        sstream >> mutated_g >> cost; // read once before loop
        while (!sstream.fail()) { //read all information in line
            //save mutated_g and cost in the current Gene array 
            find_empty_spot_mgene_cost (current_gene, mutated_g, 
            cost );
           //cout << mutated_g  << " " << cost << " ";
            sstream >> mutated_g >> cost; // save mutated gene and then cost
        }
        //cout << endl;
        sstream.clear();
    }
    infile.close();
}

/* initialize_mut_genes_and_cost
 * Input: a pointer to an array of genes and the number of unique genes.
 * Description: Initializes the mutated genes array and cost array for each gene 
 * in the genes_array by setting each value in mutated_genes to "n/a" and 
 * each cost value to 0.
 * Output: Secretly gives an array of genes whose costs and 
 * mutated genes are initialized. 
 */ 
void initialize_mut_genes_and_cost (Gene *genes_array, int num_unique_genes) {
    for (int i = 0; i < num_unique_genes; i++) { //loop over genes
        for (int j = 0; j < 5; j++) { //loop over arrays in ith gene
            //initialize elements in mutated gene array to n/a
            genes_array[i].arr_mutated_genes[j] = "n/a"; //
            //initialize elements in cost array to 0
            genes_array[i].array_costs[j] = 0;
        }
    }
}

/* find_empty_spot_mgene_cost
 * Input: Takes in a pointer to one unique gene inside the genes_array, 
 * the name of a mutated gene, and the cost associated with that mutated gene.
 * Description: To find an empty spot in the 'mutated genes' and 'cost' arrays
 * and store the mutated gene and its cost there.
 * Output: Secretly gives a unique gene that has 1 mutatated gene and 1 cost
 * stored in one of the slots that used to be available in both arrays.
 */ 
void find_empty_spot_mgene_cost (Gene *current_gene, string mutated_g, int cost ) {
    for (int j = 0; j < 5; j++) {
        //when you see empty spot 
        //[current_gene->arr_mutated_genes[j] = n/a =(current empty spot for 
        //mutated gene)]
        if ((current_gene->arr_mutated_genes[j]) == "n/a") { 
            //save mutated gene here
            current_gene->arr_mutated_genes[j] = mutated_g; 
            break; // i dont want to replace more n/a 's
        }
    }
    for (int j = 0; j < 5; j++) {
        if (current_gene->array_costs[j] == 0) { //when you see empty spot
            current_gene->array_costs[j] = cost; //save cost
            break; //don't want to replace more 0s
        }
    }
}

/* print_gene_data_check
 * Input: A pointer to an array of genes, and the number of unique genes.
 * Description: Prints out the information line by line about each gene. 
 * (For checking that the information was stored correctly).
 * Output: Printed information about the gene data.
 */ 
void print_gene_data_check (Gene *genes_array, int num_unique_genes) {
    for (int i = 0; i < num_unique_genes; i++) { //loop over genes
        string name =  genes_array[i].g_name;
        cout << name << " "; //print name of gene
        for (int j = 0; j < 5; j++) { //loop over arrays in ith gene
            string mutated_gene = genes_array[i].arr_mutated_genes[j];
            int cost = genes_array[i].array_costs[j]; 
            cout << mutated_gene  << " " << cost << " "; //print its contents
        }
        cout << endl; //space after every gene
    }
}

//------Above functions are for reading in data into the structure------//
//------Above functions are for reading in data into the structure------//


/* print_data_query
 * Input: the number of unique genes and a pointer to an array of genes.
 * Description: Prints the mutation data stored in the genes array in a
 * more readable format.
 * Output: prints to the screen the mutation data.
 */ 
void print_data_query (Gene *genes_array, int num_unique_genes) {
    for (int i = 0; i < num_unique_genes; i++) { //loop over genes
        string name =  genes_array[i].g_name;
        cout << "== " << name << " ==" << endl; //print name of gene
        cout << "Mutations:" << endl;
        for (int j = 0; j < 5; j++) { //loop over arrays in ith gene
            string mutated_gene = genes_array[i].arr_mutated_genes[j];
            int cost = genes_array[i].array_costs[j]; 
            if ((mutated_gene == "n/a") && (cost ==0)) { //really only need 1 cond
                if (j == 0) { //if the first element in array is empty, it
                    //means current gene has no mutations
                    cout << "None" << endl; //indicates it has 0 mutations
                }
                break; //stop printing 
            }
            cout << mutated_gene  << " - Cost: " << cost << endl; //print its contents
        }
        //cout << endl; //space after every gene
    }
}

/* possible_mutation_query
 * Input: the number of unique genes, a pointer to an array of genes, 
 * the source gene and target gene inputed by user, the gene index which will 
 * store where the inputed unique gene is located in the array, and
 * the index which will store the cost index where the inputed mutated gene
 * is located in the array of mutated genes of 1 unique gene.  
 * Description: Determines whether or not the source gene can mutate into the
 * target gene (both are inputs by user). Also saves the gene and cost 
 * indeces that serve the purpose described under input.
 * Output: returns a boolean indicating whether or not the the mutations is 
 * possible.
 */ 
bool possible_mutation_query (Gene *genes_array, int num_unique_genes, 
    string source_gene, string target_gene, int *gene_index, int *index_cost){
    //check 1: source_gene is one of the gene names (works)
    bool possible = true;
    int count = 0;
    //iterate over array of genes
    for (int i = 0; i < num_unique_genes; i++) { 
        string gene_name = genes_array[i].g_name;
        if (source_gene == gene_name) { //if source gene exists in array
            count++; //check 1 is passed
            *gene_index = i; //save where this equality happened
            break; //no need to check more 
        }
    }
    if (count == 0) { //that means there is no gene = to source gene
        possible = false;
        } else { //if count =1, then it passed check1. Proceed to check 2
            //check 2: check if target_gene exists in gene (= source_G) array of 
            // mutated genes
            for (int i = 0; i < 5; i++) { 
                string mutated_gene = genes_array[*gene_index].arr_mutated_genes[i];
                if (mutated_gene == target_gene) {
                    *index_cost = i;
                    count++;
                    break; // need to check more
                }
            }
            if (count == 2) {
                possible = true;
            } else { // if count is equal to 1 then
                possible = false;
            }
        }
        return possible; 
}

/* possible_mutation_energy_query
 * Input: A pointer to an array of genes, the gene index that indicates the
 * location of the inputed gene (aka source gene) in the array, the cost index
 * that indicates the location of the cost of the inputed mutated gene 
 * (aka target gene) in the array within a gene, and the energy inputed by 
 * the user.
 * Description: Determines whether or not the mutation can occur with the 
 * inputed energy or user_energy. 
 * Output: returns a boolean indicating if the mutation can 
 * occur with the inputed energy.
 */ 
bool possible_mutation_energy_query (Gene *genes_array, int gene_index, int index_cost, 
                                int user_energy){

    bool possible_2 = false; //set it to st
    int stored_cost = genes_array[gene_index].array_costs[index_cost];
    //cout << stored_cost << endl; //words
    //if the inputed energy is greater than the min energy required for mut
        if (user_energy >= stored_cost) { //fyi: energy and cost represent the same  
            possible_2 = true;
        } else { //if the inputed energy is less than the min energy
            possible_2 = false;
        }  
    return possible_2;
    }
