/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
#include <fstream>
using namespace std;

const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;
const string prompt = "Please, type the name of the file: ";
	
/* Method prototypes */
string askUserForFile(ifstream & readfile, string prompt);
bool isVowel(char ch);
bool isSentenceEnder(char ch);
int countSyllable(string str);


struct statisticsT {
	int wordCounter;
	int sentenceCounter;
	int syllableCounter;
};
	
/* checks whether or not character is a vowel */
bool isVowel(char ch){
	string vowels = "AEIOUYaeiouy";
	if(vowels.find(ch) == -1) return false;
	return true;
}

/* checks whether or not character is something a sentence could end with */
bool isSentenceEnder(char ch){
	string enders = ".?!";
	if(enders.find(ch) != -1) return true;
	return false;
}

/* counts the syllables in the word with the given rule */
int countSyllable(string str){
	int counter = 0;
	if(!isalpha(str[0]) && str.length() == 1) return 0;
	if(str.length() >=2)
		if(str[str.length()-1] == 'e' && isVowel(str[str.length()-2])) counter++;
    for(int i = 0; i < str.length() - 1; i++){
        if(isVowel(str[i])){
            if(!isVowel(str[i+1])){
                counter++;
            }
        }
    }	
	if(isVowel(str[str.length()-1]) && str[str.length()-1] != 'E' && str[str.length()-1] != 'e')
		counter++;
	if(counter <= 1) return 1;
	return counter;
}

/* reads the file, scanns it, and counts syllables, sentences and words, returns
the struct with the information about statistics of words and sentences inside */
statisticsT calculateData(){
	statisticsT result;
	ifstream readfile;
	string line;
	result.wordCounter = 1;
	result.sentenceCounter = 1;
	result.syllableCounter = 0;
	string filename = askUserForFile(readfile, prompt);
	readfile.open(filename.c_str());
	TokenScanner scanner;
	while(getline(readfile, line)){
		scanner.setInput(line);
		scanner.ignoreWhitespace();				
		scanner.addWordCharacters("'"); // <- including this as a part of the word;
		while(scanner.hasMoreTokens()){
			string curr = scanner.nextToken();
			if(isalpha(curr[0])){
				result.wordCounter++;
				result.syllableCounter += countSyllable(curr);
			}
			if(isSentenceEnder(curr[0])) result.sentenceCounter++;
		}
	}
	return result;
}

/* asks user to give the file input, until correct file name is typed
in the console, if the name is wrong, text is displayed */
string askUserForFile(ifstream & readfile, string prompt){
	while(true){
		cout << prompt;
		string nameOfFile;
		getline(cin, nameOfFile);
		readfile.open(nameOfFile.c_str());
		if(!readfile.fail()){ 
			readfile.close();
			return nameOfFile;
		}
		readfile.clear();
		cout << "Unable to open that file, please try again. " << endl;
	}
}

/* Main program */
int main() {
	statisticsT stat = calculateData();
	// the case where we avoid dividing by 0 while calculating the formula
	if(stat.sentenceCounter != 1) stat.sentenceCounter--;
	if(stat.wordCounter != 1) stat.wordCounter--;
	double firstPart = C1 * ((double)stat.wordCounter / stat.sentenceCounter);
	double secondPart = C2 * ((double)stat.syllableCounter / stat.wordCounter);
	double gradeLevel = C0 + firstPart + secondPart;
	cout << "Words: " << stat.wordCounter << endl;
	cout << "Syllables: " << stat.syllableCounter << endl;
	cout << "Sentences: " << stat.sentenceCounter << endl;
	cout << "Grade level: " << gradeLevel << endl;
	return 0;
}
