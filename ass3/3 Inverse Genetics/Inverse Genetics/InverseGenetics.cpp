/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

const string SENTINEL = ""; 
const string PROMPT = "insert protein or empty string to break: ";

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

void listAllRec(string protein, Map<char, Set<string> > &codons, Vector<string> &curr);

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	string protein;
	while(true){
		protein = getLine(PROMPT);
		if(protein == SENTINEL) break;
		listAllRNAStrandsFor(protein, codons);
	}
    return 0;
}

void listAllRec(string protein, Map<char, Set<string> > &codons, Vector<string> &curr){
	if(protein.empty()){
		for(int i = 0; i < curr.size(); i++){
			cout << curr[i];
		}
		cout << endl;
		return;
	}
	Set<string> toIterateOver = codons[protein[0]];
	foreach(string key in toIterateOver){
		curr.add(key);
		listAllRec(protein.substr(1), codons, curr);
		curr.remove(curr.size() - 1);
	}	
}

/* Wrapper Function */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> > &codons){
	Vector<string> temp;
	listAllRec(protein, codons, temp);
}


/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
