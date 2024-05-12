/*
 * lineage.cpp
 * Purpose: To read in the file with mutation data into the struct created,
 * and perform the queries necessary chosen by the user.
 *  {Javier Laveaga AND jlavea01}
 * */
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
//Jav
bool evolve_query(Gene *src, Gene *tgt);
int evolution_steps_query (Gene *src, Gene *tgt, int num_steps);
int energetic_ev_query (Gene *src, Gene *tgt, int min_energy);
void evo_path_query (Gene *src, Gene *tgt);


int main(){

    Gene *dna;

    //After this line executes, dna is a pointer to the array of gene
    //information read in from a given data file, and num_nodes contains the
    //number of genes stored in that array. 
    int num_nodes = create_graph(&dna);
    //USE dna AND num_nodes AFTER THIS LINE TO CONTINUE THE COMPUTATION 
    cin.ignore();  //to ignore \n in the file input
    string line_in;
    string query;
    cout << "Enter a query: "; 
    stringstream sstream;
    while (getline(cin, line_in)) { //will keep asking the user for input
        sstream.str(line_in);
        sstream >> query; //first part of the line
        if (query == EVOLVE) {
            bool evolve;
            string source_gene, target_gene;
            sstream >> source_gene;
            sstream >> target_gene;
            int index_src = index_of(dna, source_gene, num_nodes); 
            int index_tgt = index_of(dna, target_gene, num_nodes);
            //two lines above will return -1 if there is no gene that
            // matches what the user inputted. 
            //So it will seg fault if the user gives invalid input

            //just in case user inputs invalid gene sequences 
            //(so that I dont get a seg fault)
            if (index_src == -1 || index_tgt == -1) {
                evolve = false;
            } else {
                Gene *src = &dna[index_src];
                Gene *tgt = &dna[index_tgt];
                evolve = evolve_query(src, tgt);
            }

            if (evolve) {
                cout << source_gene << " can evolve into " << target_gene;
                cout << endl;
            } else {
                cout << source_gene << " cannot evolve into " << target_gene;
                cout << endl;
            }
            //reset the seen back to false before next query iteration
            for (int i = 0; i < num_nodes; i++) {
                dna[i].seen = false;
            }

        } else if (query == E_STEPS) {
            int n; //number of steps
            string source_gene, target_gene;
            sstream >> source_gene;
            sstream >> target_gene;
            int index_src = index_of(dna, source_gene, num_nodes); 
            int index_tgt = index_of(dna, target_gene, num_nodes);
            
            if (index_src == -1 || index_tgt == -1) {
                n = -1;
            } else {
                Gene *src = &dna[index_src];
                Gene *tgt = &dna[index_tgt];
                int num_steps = 1; 
                n = evolution_steps_query (src, tgt, num_steps);
                //n & num_steps are the same thing
            }
            if (n != -1) {
                cout << "It will take " << n << 
                " evolutionary steps to get from " << source_gene << 
                " to " << target_gene;
                cout << endl;
            } else {
                cout << "It will take " << n << 
                " evolutionary steps to get from " << source_gene << 
                " to " << target_gene;
                cout << endl;
            }
            //reset the seen back to false before next query iteration
            for (int i = 0; i < num_nodes; i++) {
                dna[i].seen = false;
            }
            
        } else if (query == ENE_EVOLVE) {
            int min_energy = 0;
            int energy_in = 0;
            string source_gene, target_gene;
            sstream >> source_gene;
            sstream >> target_gene;
            sstream >> energy_in;
            //Get source and target index in array of genes
            int index_src = index_of(dna, source_gene, num_nodes); 
            int index_tgt = index_of(dna, target_gene, num_nodes);
            
            if (index_src == -1 || index_tgt == -1) {
                min_energy = -1;
            } else {
                Gene *src = &dna[index_src];
                Gene *tgt = &dna[index_tgt];
                //if the first source gene has a mutation
                if (src->muts != nullptr) { 
                    //make that the starting min cost
                    min_energy = src->muts->cost; 
                }
                //call the function to add to that min cost
                //delete the folllowing cout statement
                //cout << index_src << " " << index_tgt << " " << min_energy << endl;
                min_energy = energetic_ev_query (src, tgt, min_energy);
                //cout << min_energy << endl;
            }
            if (min_energy == -1) { //if it can't evolve at all
                cout << source_gene << " cannot evolve into " << target_gene << 
                " with at most " << energy_in << " evolutionary cost";
                cout << endl;
            } else if (energy_in >= min_energy) {
                cout << source_gene << " can evolve into " << target_gene << 
                " with at most " << energy_in << " evolutionary cost";
                cout << endl;
            } else { //if not inputted enegy not greater than energy required
                cout << source_gene << " cannot evolve into " << target_gene << 
                " with at most " << energy_in << " evolutionary cost";
                cout << endl;
            }
            
            //reset the seen back to false before next query iteration
            for (int i = 0; i < num_nodes; i++) {
                dna[i].seen = false;
            }
        } else if (query == PATH) {
            bool evolve;
            string source_gene, target_gene;
            sstream >> source_gene;
            sstream >> target_gene;
            int index_src = index_of(dna, source_gene, num_nodes); 
            int index_tgt = index_of(dna, target_gene, num_nodes);
            Gene *src;
            Gene *tgt;
            
            if (index_src == -1 || index_tgt == -1) {
                evolve = false;
            } else {
                src = &dna[index_src];
                tgt = &dna[index_tgt];
                evolve = evolve_query(src, tgt);
            }
            if (evolve) { //if it can evolve, then print the steps
                evo_path_query(src, tgt);
            } else {
                cout << "There is no path from " << source_gene << " to " 
                << target_gene << endl;
            }
        
            //reset the seen back to false before next query iteration
            for (int i = 0; i < num_nodes; i++) {
                dna[i].seen = false;
            }

        } else if (query == QUIT) { 
            //delete mutations
            for (int i = 0; i < num_nodes; i++) {
                delete dna[i].muts;  
            }
            //delete gene array
            delete [] dna;
            return 0; // this exits the program, the main program
        } else {
            cout << query << " not recognized." << endl;                             
        }
        cout << endl << "Enter a query: ";
        sstream.clear(); //very important
        }
    //Deleting memory

    //delete the mutation allocated memory
    for (int i = 0; i < num_nodes; i++) {
        delete dna[i].muts; //the array brackets already derefences it. 
        //= (*dna[i].muts) not sure
    }
    //delete the array of genes allocated
    delete [] dna;
    
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
    *dna_p = new Gene[num_nodes]; //dereferences pointer to a pointer,
    // which gives acces to the pointer. of gene structures.
    //not the same as in the mutations since you are not delcaring 
    //here with "GENE" on the left.
    ///you are updating
    init(*dna_p, num_nodes);
    populate_nodes(*dna_p, &inf, num_nodes);

    // Reset the file to read the links
    inf.close();
    inf.open(filename);
    inf >> num_nodes;
    inf.ignore();

    populate_links(*dna_p, &inf, num_nodes); //dereferencing dna_p, gives you 
    //pointer to array of genes (b/c dna_p is a pointer to a pointer 
    //of array of genes)
    
    return num_nodes;
}

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
    int cost;
    //int next_spot;
    for (int i = 0; i < num_nodes; i++) {
        getline(*inf, line);

        sstr.str(line);
        sstr >> seq;//Skip over first gene name on each line
        
        // Add a mutation if it exists
        sstr >> mut_seq >> cost;
        if (!sstr.fail()) { // if you haven't reached end of file. 
        //(this is just to account for genes w/ no mutation)
            //finds where the mutated gene is in gene
            int mut_index = index_of(dna, mut_seq, num_nodes);  
            //array (first name). So where the mut_gene on right is on the left.
            //allocats memeory for a single mutation structure.
            dna[i].muts = new Mutation; 
            //stores the address in dna[i].muts. (creates mutation for current gene)
            dna[i].muts->cost = cost;
            dna[i].muts->target = &dna[mut_index]; //assigns target 
            //pointer of mutation to the 
            //address of where it is located in gene array name. (string sq)
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

// evolve_query
// Input: The source gene (src) and the target gene (tgt) We assume these
//        are represented with pointers into an array of genes that is 
//        initialized.
// Description: Determines if a gene can evolve into another gene.
// Output: a boolean indicating whether src can evolve into tgt.
bool evolve_query(Gene *src, Gene *tgt) {
    
    //bool evolve;
    //1.If src cannot mutate into another gene, it definitely 
    //cannot evolve into tgt.
    if (src->muts == nullptr) { 
        return false;
    }
    //2.If src can mutate into tgt, 
    //then it can evolve into tgt in one step!
    if(src->muts->target->sq == tgt->sq  ) {
        return true;
    }
    
    //Here
    // 3. If src was already “seen”, then tgt is not reachable 
    //from src via mutations
    
    if (src->seen == true) {
        return false;
    }

    src->seen = true; //set source (genes on the left) to seen
    Gene *new_src = src->muts->target; // mutation of source becomes new source

    return evolve_query(new_src, tgt);

}

// evolution_steps_query
// Input: The source gene (src) and the target gene (tgt). These
//        are represented with pointers into an array of genes that is 
//        initialized. The other input is an integer to store the number
//        of steps in the evolution.
// Description: Determines the number of mutations it takes for a source 
//              gene to evolve to a target gene.
// Output: Gives the number of evolutionary steps it takes to get from 
//         source to target. If the evolution is not possible, it returns
//         negative one.
int evolution_steps_query (Gene *src, Gene *tgt, int num_steps) {
     //bool evolve;
    //1.If src cannot mutate into another gene, it definitely 
    //cannot evolve into tgt.
    if (src->muts == nullptr) { 
        //return false;
        return -1;
    }
    //2.If src can mutate into tgt, 
    //then it can evolve into tgt in one step!
    if(src->muts->target->sq == tgt->sq  ) {
        //return true;
        return num_steps;
    }
    // 3. If src was already “seen”, then tgt is not reachable 
    //from src via mutations
    
    if (src->seen == true) {
       // return false;
       return -1;
    }

    src->seen = true; //set source (genes on the left) to seen
    Gene *new_src = src->muts->target; // mutation of source becomes new source
    num_steps++;
    return evolution_steps_query(new_src, tgt, num_steps);
}

// energetic_ev_query
// Input: The source gene (src) and the target gene (tgt). We assume these are 
//        represented by pointers into an initialized array of genes. The other 
//        input is an integer to store the minimum energy required. It is
//        initially set to be the cost of the first mutation (if possible).
// Description: Determines whether the source can evolve into the target 
//              and the minimum energy required to do so.
// Output: an integer indicating the minimum amount of energy necessary to 
//         evolve to the target gene. Returns -1 if the evolution is not
//         possible. 
int energetic_ev_query (Gene *src, Gene *tgt, int min_energy) {
    //1.If src cannot mutate into another gene, it definitely 
    //cannot evolve into tgt.
    if (src->muts == nullptr) { 
        //return false;
        return -1;
    }
    //2.If src can mutate into tgt, 
    //then it can evolve into tgt in one step!
    if(src->muts->target->sq == tgt->sq  ) {
        //return true;
        return min_energy;
    }
    // 3. If src was already “seen”, then tgt is not reachable 
    //from src via mutations
    
    if (src->seen == true) {
       // return false;
       return -1;
    }

    src->seen = true; //set source (genes on the left) to seen
    Gene *new_src = src->muts->target; // mutation of source becomes new source
    min_energy = min_energy + new_src->muts->cost;
    return energetic_ev_query(new_src, tgt, min_energy);
}

// evo_path_query 
// Input: The source gene (src) and the target gene (tgt). We assume these are 
//        represented by pointers into an initialized array of genes.
//        It assumes that the source can evolve into the target gene.
// Description: Prints out the sequence of mutations from the source gene
//              to the target gene.
// Output: It prints out the sequence of mutations from the source to the 
//         target gene.       
void evo_path_query (Gene *src, Gene *tgt) {
    cout << src->sq << " -> "; //print source
    //2.If src can mutate into tgt, 
    //then it can evolve into tgt in one step!
    if(src->muts->target->sq == tgt->sq  ) {
        cout << tgt->sq << endl;
        return;
    }
    Gene *new_src = src->muts->target; // mutation of source becomes new source
    evo_path_query(new_src, tgt);
    return; 
}
