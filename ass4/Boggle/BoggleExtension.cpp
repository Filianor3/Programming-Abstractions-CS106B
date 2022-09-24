#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* direction massives */
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0 ,1};

/* Function prototypes */
void welcome();
void giveInstructions();
void setUpBoard(Grid<char> &board);
bool func(string word, Lexicon &lex, Grid<char> &board, Grid<bool> &usedCells, Set<string> &playerWords);
bool wordFinderRec(string word, Lexicon &lex, Grid<char> &board, Grid<bool> &usedCells, int x, int y, Set<string> &playerWords);
void wordFinder(string word, Lexicon &lex, Grid<char> &board, Set<string> &playerWords);
void playersTurn(Lexicon &lex, Grid<char> &board, Set<string> &playerWords);
void computerCheckRec(Lexicon &lex, Grid<char> &board, Grid<bool> &usedCells, string currentWord, int x, int y, Set<string> &playerWords,
					  Set<string> &computerWords);
void computerCheck(Lexicon &lex, Grid<char> &board, Grid<bool> &usedCells, Set<string> &playerWords, Set<string> &computerWords);
void computersTurn(Lexicon &lex, Grid<char> &board, Set<string> &playerWords, Set<string> &computerWords);

/* draws the board and puts each random letter from the string in grid */
void setUpBoard(Grid<char> &board){
	int N_ROWS = getInteger("insert number of rows: ");;
	int N_COLS = getInteger("insert number of columns: ");
	int ifCustom = N_ROWS * N_COLS;
	drawBoard(N_ROWS, N_COLS);
	Vector<string> cubesVec;
	string answer = getLine("Would you like to play with our characters? type yes or anything else for no: ");
	if(answer == "yes"){
		foreach(string tmp in STANDARD_CUBES){
			cubesVec.add(tmp);
		}
		int currStrIndex = 0;
		for(int i = 0; i < board.nRows; i++){
			for(int j = 0; j < board.nCols; j++){
				string currentString = cubesVec.get(currStrIndex);
				int randIndex = randomInteger(0, currentString.length() - 1);
				char currSymbol = currentString[randIndex];
				board[i][j] = currSymbol;
				labelCube(i, j, currSymbol);
				currStrIndex++;
			}
		}
	}else{
		string prompt = "Type " + ifCustom + " characters for custom input: "; 
		string answer = getLine(prompt);
		while(true){
			if(answer.length() == 16){
				break;
			}else{
				answer = getLine(prompt);
			}
		}
		answer = toUpperCase(answer);
		int currIndex = 0;
		for(int i = 0; i < board.nRows; i++){
			for(int j = 0; j < board.nCols; j++){
				board[i][j] = answer[currIndex];
				labelCube(i, j, board[i][j]);
				currIndex++;
			}
		}
	}
}

/* checks whether the first symbol of word can be found in the grid then calls the recursive function on substring */
bool func(string word, Lexicon &lex, Grid<char> &board, Grid<bool> &usedCells, Set<string> &playerWords){
	for(int i = 0; i < board.nRows; i++){
		for(int j = 0; j < board.nCols; j++){
			usedCells[i][j] = true;
			if(board[i][j] == word[0] && wordFinderRec(word.substr(1), lex, board, usedCells, i, j, playerWords)){
				return true;
			}
			usedCells[i][j] = false;
		}
	}
	return false;
}

/* recursive method which finds the destination word and highlights it if its found */
bool wordFinderRec(string word, Lexicon &lex, Grid<char> &board, Grid<bool> &usedCells, int x, int y, Set<string> &playerWords){
	if(word.length() == 0){
		return true;
	}
	for(int i = 0; i < 8; i++){
		if(board.inBounds(x + dx[i], y + dy[i]) && word[0] == board[x + dx[i]][y + dy[i]] && !usedCells[x + dx[i]][y + dy[i]]){
			usedCells[x + dx[i]][y + dy[i]] = true;
			if(wordFinderRec(word.substr(1), lex, board, usedCells, x + dx[i], y + dy[i], playerWords)){
				highlightCube(x + dx[i], y + dy[i], true);
				pause(100);
				highlightCube(x + dx[i], y + dy[i], false);
				return true;
			}
			usedCells[x + dx[i]][y + dy[i]] = false;
		}	
	}
	return false;
}

/* prints whether or not the word is correct */
void wordFinder(string word, Lexicon &lex, Grid<char> &board, Set<string> &playerWords){
	Grid<bool> usedCells(board.nRows, board.nCols);
	for(int i = 0; i < usedCells.nRows; i++){
		for(int j = 0; j < usedCells.nCols; j++){
			usedCells[i][j] = false;
		}
	}
	if(func(word, lex, board, usedCells, playerWords)){
		if(!playerWords.contains(toLowerCase(word))){
			recordWordForPlayer(toLowerCase(word), HUMAN);
			playerWords.add(toLowerCase(word));
			cout << "Correct Guess" << endl;
		}else{
			cout << "Already used word" << endl;	
		}
	}else{
		cout << "No such word was found on the board." << endl;
	}
	return;
}

/* asks the player to type words until he is finished guessing */
void playersTurn(Lexicon &lex, Grid<char> &board, Set<string> &playerWords){
	while(true){
		string currentGuess = getLine("Enter a word: ");
		if(currentGuess == ""){
			return;
		}
		currentGuess = toUpperCase(currentGuess);
		if(currentGuess.size() < 4){
			cout << "Minimum size of the word should be 4 characters." << endl;
		}else if(!lex.contains(currentGuess)){
			cout << "No such word exists in the lexicon." << endl;
		}else{
			wordFinder(currentGuess, lex, board, playerWords);
		}
	}
}

/* checks if such word is found in the lexicon recursively and adds it to set of computer words */
void computerCheckRec(Lexicon &lex, Grid<char> &board, Grid<bool> &usedCells, string currentWord, int x, int y, Set<string> &playerWords,
					  Set<string> &computerWords){
	if(lex.contains(currentWord) && currentWord.length() >= 4){
		if(!playerWords.contains(toLowerCase(currentWord)) && !computerWords.contains(toLowerCase(currentWord))){
			recordWordForPlayer(currentWord, COMPUTER);
			computerWords.add(toLowerCase(currentWord));
		}
	}
	for(int i = 0; i < 8; i++){
		if(board.inBounds(x + dx[i], y + dy[i]) && usedCells[x + dx[i]][y + dy[i]] == false && lex.containsPrefix(currentWord)){
				usedCells[x + dx[i]][y + dy[i]] = true;
				computerCheckRec(lex, board, usedCells, currentWord + board[x + dx[i]][y + dy[i]], x + dx[i], y + dy[i], playerWords, computerWords);
				usedCells[x + dx[i]][y + dy[i]] = false;
		}
	}
}

/* takes first letter of the alphabet and calls recursive function */
void computerCheck(Lexicon &lex, Grid<char> &board, Grid<bool> &usedCells, Set<string> &playerWords, Set<string> &computerWords){
	for(int i = 0; i < board.nRows; i++){
		for(int j = 0; j < board.nCols; j++){
			string str = "";
			str += board[i][j];
			usedCells[i][j] = true;
			computerCheckRec(lex, board, usedCells, str, i, j, playerWords, computerWords);
			usedCells[i][j] = false;
		}
	}
}

/* creates used cells board of booleans and calls redcursive function */
void computersTurn(Lexicon &lex, Grid<char> &board, Set<string> &playerWords, Set<string> &computerWords){
	Grid<bool> usedCells(board.nRows, board.nCols);
	for(int i = 0; i < usedCells.nRows; i++){
		for(int j = 0; j < usedCells.nCols; j++){
			usedCells[i][j] = false;
		}
	}
	computerCheck(lex, board, usedCells, playerWords, computerWords);
}

/* Main program */
int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
	giveInstructions();
	Lexicon lex("EnglishWords.dat");
	while(true){
		Grid<char> board(N_ROWS, N_COLS);
		Set<string> playerWords;
		Set<string> computerWords;
		setUpBoard(board);
		playersTurn(lex, board, playerWords);
		computersTurn(lex, board, playerWords, computerWords);
		string answer = getLine("Do you want to play again? yes or anything else to break: ");
		if(answer == "yes"){
			continue;
		}else{
			break;
		}
	}
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */
void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

