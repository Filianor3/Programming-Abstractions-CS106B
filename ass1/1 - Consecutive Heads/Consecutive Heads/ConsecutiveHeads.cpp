#include <iostream>
#include "console.h"
#include "simpio.h"
#include "random.h"
using namespace std;

/*This method randoms the bool with
the chance of true or false (50% each)
returns "heads" if the value is true
else "tails" */
string flip(){
	if(randomChance(0.5)){
		cout << "heads" << endl;
		return "heads";
	}else{
		cout << "tails" << endl;	
		return "tails";
	} 
}

/* Main program */
int main0() {
	double sum = 0;
	int counter = 0;
	int attempts = 0;
	while(counter != 3){
		attempts++;
		if(flip() == "heads") counter++;
		else counter = 0;
	}
	cout << "It took " << attempts << " flips to get 3 consicutive heads." << endl;
	return 0;
}
