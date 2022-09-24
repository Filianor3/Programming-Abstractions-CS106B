/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* returns the n-th and k-th element of the pascal triangle */
int pascalTriangle(int n, int k){
	return ((k == 0) || (n == k)) ? 1 : (pascalTriangle(n-1, k-1) + pascalTriangle(n-1, k)); 
}

/* Main program */
int main() {
	int n,k;
	n = getInteger("n: ");
	k = getInteger("k: ");
	if(k > n){
		cout << "k cannot be more than n, please give us the valid input" << endl;	
	}else{
		cout << "c(" << n << "," << k << ") element is " << pascalTriangle(n, k) << endl;
	}
	return 0;
}
