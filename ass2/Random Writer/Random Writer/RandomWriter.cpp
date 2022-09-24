#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "vector.h"
#include "map.h"
#include "simpio.h"
#include "foreach.h"
#include "random.h"

using namespace std;

const string PROMPT = "Enter the source text: ";
const string ERROR_MESSAGE = "Unable to open file with that name, please try again.";
const int CHARACTER_AMOUNT = 2000;

/* asks user to give the filename unless its a valid
filename which can be opened
*/
string promptUser(ifstream & input){
	while(true){
		cout << PROMPT;
		string filename;
		getline(cin, filename);
		input.open(filename.c_str());
		if(!input.fail()){
			input.close();
			return filename;
		} 
		input.clear();
		cout << ERROR_MESSAGE << endl;
	}
	
}

/* opens the file, builds the starter word consisting of K characters
then grabs the next Key for the map by removing the 0-th
character and adding next character to the current string
keeps all the data in the map
*/
void collectTheData(Map<string, Vector<char>> &data, int k, ifstream &infile, string filename){	
	infile.open(filename.c_str());
	string currTxt;
	char ch;	
	for(int i = 0; i < k; i++){
		infile.get(ch);
		currTxt += ch;
	}
	while(infile.get(ch)){
		data[currTxt].add(ch);
		currTxt = currTxt.substr(1) + ch; 
	}
	infile.close();
}

/* finds the most popular word (character sequence)
in the text by simply, iterating over the map
and choosing the key with the biggest vector size
*/
string popularWord(Map<string, Vector<char>> &data){
	string mostOccured;
	int maxOccurence = 0;
	foreach(string key in data){
		if(maxOccurence < data[key].size()){
			maxOccurence = data[key].size();
			mostOccured = key;
		}
	}
	return mostOccured;
}

/* randomises the character sequence, based on the 
map we created based on the text file given
*/
void randomiseText(Map<string, Vector<char>> &data, int k){
	string mostPopular = popularWord(data);
	string currentWord = mostPopular;
	string answer = currentWord;
	int counter = k;
	while(counter != CHARACTER_AMOUNT){
		if(data[currentWord].size() == 0) break;
		int rand = randomInteger(0,data[currentWord].size()-1);
		char currCh = data[currentWord].get(rand);
		currentWord = currentWord.substr(1) + currCh;
		answer += currCh;
		counter++;
	}
	cout << answer << endl;
}

/* asks user for the inputs, and calls the collectdata 
function
*/
void analyzeText(){
	ifstream infile;
	int k;
	Map<string, Vector<char>> data;
	string filename = promptUser(infile);
	while(true){
		k = getInteger("Enter the Markov order [1-10]: ");
		if(k >= 1 && k <= 10) break;
		else cout << "Invalid input." << endl;
	}
	collectTheData(data, k, infile, filename);
	randomiseText(data, k);
}

/* Main program */
int main() {
	analyzeText();
    return 0;
}