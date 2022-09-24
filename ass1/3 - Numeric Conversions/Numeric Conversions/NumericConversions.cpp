/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */
string intToString(int n);
int stringToInt(string str);


/* Converts string to int with recursion */
int stringToInt(string str){
	int len = str.length();
	if(len == 0) return 0;
	if(str[0] == '-') return (stringToInt(str.substr(1, len - 2)) * 10 + str[(len - 1)] - '0') * -1;
	return stringToInt(str.substr(0, len - 1)) * 10 + str[(len - 1)] - '0';
}

/* Converts int to string with recursion */
string intToString(int n){
	/* edge case of integer's min value */
	if(n == INT_MIN) return "-2147483648";
	if(n < 0) return "-" + intToString(n * -1);
	if(n <= 9) return string()+(char(n + '0'));
	return intToString(n/10) + string()+(char(n%10 + '0')) ;
}

/* Main program */
int main() {
	cout << "string to int: " << stringToInt("-4") << endl;
	cout << "string to int: " << stringToInt("-13") << endl;
	cout << "string to int: " << stringToInt("13") << endl;
	cout << "string to int: " << stringToInt("4") << endl;
	cout << "string to int: " << stringToInt("214124") << endl;
	cout << "string to int: " << stringToInt("0") << endl;
	cout << "int to string: " << intToString(4) << endl;
	cout << "int to string: " << intToString(13) << endl;
	cout << "int to string: " << intToString(-13) << endl;
	cout << "int to string: " << intToString(-4) << endl;
	cout << "int to string: " << intToString(0) << endl;
	cout << "int to string: " << intToString(INT_MIN) << endl;
    return 0;
}
