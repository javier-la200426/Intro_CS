//TODO: WRITE YOUR HEADER COMMENT :-)
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
struct Gene;

struct Mutation {
    int cost;
    Gene *target;
};

struct Gene {
    string sq;
    bool seen; //Used in recursive functions to avoid loops
    Mutation *muts;
};

const string EVOLVE = "e";
const string E_STEPS = "es";
const string ENE_EVOLVE = "ene";
const string PATH = "path";
const string QUIT = "q";


int  create_graph(Gene **);
void populate_nodes(Gene *dna, ifstream *inf, int num_nodes);
void populate_links(Gene *dna, ifstream *inf, int num_nodes);
int  index_of(Gene *, string, int);
void init(Gene *, int);


int main(){

    Gene *dna;

    //After this line executes, dna is a pointer to the array of gene
    //information read in from a given data file, and num_nodes contains the
    //number of genes stored in that array. 
    int num_nodes = create_graph(&dna);

    //USE dna AND num_nodes AFTER THIS LINE TO CONTINUE THE COMPUTATION
    
    return 0;
}



// Creates graph and stores it inside of array at passed location.
// create_graph 
// Input: An uninitialized pointer to a Gene pointer.
// Description: Read in a file provided the user and use the data to populate an
//              array of Genes.
// Output: Populates the array pointed to by *dna_p with the contents of a data
//         file, and returns the number of array elements
int create_graph(Gene **dna_p){
    string filename;
    cout << "Enter data file name: ";
    cin >> filename;

    ifstream inf(filename);
    if (inf.fail()) {
        cerr << "ERROR OPENING FILE: Exiting Program" << endl;
        exit(EXIT_FAILURE);
    }
    
    int num_nodes;
    inf >> num_nodes;
    inf.ignore(); 
    
    // Create and populate the nodes in the array
    *dna_p = new Gene[num_nodes];
    init(*dna_p, num_nodes);
    populate_nodes(*dna_p, &inf, num_nodes);

    // Reset the file to read the links
    inf.close();
    inf.open(filename);
    inf >> num_nodes;
    inf.ignore();

    populate_links(*dna_p, &inf, num_nodes);
    
    return num_nodes;
}

// init 
// Input: A pointer to an uninitialized array of genes and the size of 
//        that array.
// Description: Initializes the array of genes with non-garbage information.
// Output: Initializes the array pointed to by 'dna'.
void init(Gene *dna, int num_nodes){
    for (int i = 0; i < num_nodes; i++) {
        dna[i].sq = "";
        dna[i].seen = false;
        dna[i].muts = nullptr;
    }
}

// populate_nodes
// Input: A pointer to an array of genes, a pointer to a file, 
//        and the size of the array.
// Description: Read the file and populate the genes in the array with their
//              sequence information.
// Output: Populates the sequence information for the gene array pointed to by
//         'dna'. Moves the file pointer further into the file.
void populate_nodes(Gene *dna, ifstream *inf, int num_nodes){
    string line;
    stringstream sstr;
    for (int i = 0; i < num_nodes; i++) {
        getline(*inf, line);
        sstr.str(line);
        sstr >> dna[i].sq;
        sstr.clear();
    }
}

// populate_links
// Input: A pointer to an array of genes, a pointer to a file, 
//        and the size of the array.
// Description: Read the file and populate the mutation information between
//              genes in the array. We assume the data file only contains
//              well-formed input.
// Output: Populates the mutation information for the gene array pointed to by
//         'dna'. Moves the file pointer further into the file.
void populate_links(Gene *dna, ifstream *inf, int num_nodes){
    string line, seq, mut_seq;
    stringstream sstr;
    int cost, next_spot;
    for (int i = 0; i < num_nodes; i++) {
        getline(*inf, line);

        sstr.str(line);
        sstr >> seq;//Skip over first gene name on each line
        
        // Add a mutation if it exists
        sstr >> mut_seq >> cost;
        if (!sstr.fail()) {
            int mut_index = index_of(dna, mut_seq, num_nodes);
            dna[i].muts = new Mutation;
            dna[i].muts->cost = cost;
            dna[i].muts->target = &dna[mut_index];
        }
        //Prepare to read another line from this string stream
        sstr.clear();
    }
}

// index_of
// Input: An array of genes, a gene sequence, and the size of the array.
// Description: Find the index of the given sequence in the array.
// Output: The index of the sequence in the array, or -1 if the sequence is not
//         in the array.
int index_of(Gene *dna, string seq, int num_nodes){
  for (int i = 0; i < num_nodes; i++) {
    if (dna[i].sq == seq) {
      return i;
    }
  }
  return -1;
}
