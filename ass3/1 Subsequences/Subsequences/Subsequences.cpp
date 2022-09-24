#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

const string SENTINEL = "turn off";

bool isSubsequence(string text, string subsequence);

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence){
	if((text == "" && subsequence == "") || (subsequence == "")) return true;
	if(text == "") return false;
	if(text[0] == subsequence[0]){
		return isSubsequence(text.substr(1), subsequence.substr(1));
	}else{
		return isSubsequence(text.substr(1), subsequence);
	}	
}

/* Main program */
int main() {
	while(true){
		string text = getLine("insert text string: ");
		if(text == SENTINEL) break;
		string subsequent = getLine("insert subsequent string: ");
		if(isSubsequence(text, subsequent)){
			cout << subsequent << " IS A SUBSEQUENCE OF " << text << endl;
		}else {
			cout << subsequent << " IS NOT SUBSEQUENCE OF " << text << endl;
		}
	}
    return 0;
}
