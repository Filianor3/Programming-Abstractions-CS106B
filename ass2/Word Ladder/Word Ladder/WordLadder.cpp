#include <iostream>
#include <string>
#include "queue.h"
#include "console.h"
#include "lexicon.h"
#include "vector.h"
#include "set.h"
#include "foreach.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

const string START = "Enter start word (or nothing to quit): ";
const string DESTINATION = "Enter destination word: ";
const string LADDER = "Found ladder: ";
const string NO_LADDER = "No ladder found.";
const string SENTINEL = "";

/* prints the ladder in the console */
void printLadder(Vector<string> &ladder){
	cout << LADDER;
	for(int i = 0; i < ladder.size() - 1; i++){
		cout << ladder[i] + " -> "; 
	}
	cout << ladder[ladder.size()-1] << endl;
}

/* returns the set, which consists of all the words, that are 
in lexicon and are only symbol different from the last word
of the current vector
*/
Set<string> allPossibilities(Vector<string> &ladder, Lexicon &lexicon){
	string wordToConstruct = ladder[ladder.size()-1];
	string cpy = wordToConstruct;
	Set<string> toReturn;
	for(int i = 0; i < wordToConstruct.length(); i++){
		for(char ch = 'a'; ch <= 'z'; ch++){
			cpy[i] = ch;
			if(lexicon.contains(cpy) && cpy != ladder[ladder.size()-1])
				toReturn.add(cpy);
		}
		cpy = wordToConstruct;
	}
	return toReturn;
}

/* finds the shortest way from the beginning string to
the ending string, prints the ladder in the console if
such ladder was found, else just prints the message
*/
void buildLadder(string beginning, string ending){
	Lexicon lexicon("EnglishWords.dat");
	Queue<Vector<string>> ladder;
	Vector<string> copyPath;
	Set<string> allUsedWords;
	Vector<string> path;
	path.add(beginning);
	ladder.enqueue(path);
	while(!ladder.isEmpty()){
		Vector<string> currLadder = ladder.dequeue();
		if(currLadder[currLadder.size() - 1] == ending){
			printLadder(currLadder);
			return;
		}
		Set<string> validWords = allPossibilities(currLadder, lexicon);
		foreach(string str in validWords){
			if(!allUsedWords.contains(str)){
				copyPath = currLadder;
				copyPath.add(str);
				ladder.enqueue(copyPath);
				allUsedWords.add(str);
			}
		}
	}
	cout << NO_LADDER << endl;
}

/* main program */
int main() {
	string beginning, ending;
	while(true){
		beginning = getLine(START);
		if(toLowerCase(beginning) == SENTINEL) break;
		ending = getLine(DESTINATION);
		buildLadder(toLowerCase(beginning), toLowerCase(ending));
	}
	cout << "Goodbye." << endl;
	return 0;
}
