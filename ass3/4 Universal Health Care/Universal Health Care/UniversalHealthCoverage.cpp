/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

/* Checks whether our result Vector of sets, contains the same
coverage of cities as cities Set<>;
*/
bool checkFinalAnswer(Set<string> & cities, Vector< Set<string> > &result){
	Set<string> myCoveredCities;
	foreach(Set<string> curr in result){
		foreach(string s in curr){
			myCoveredCities.add(s);
		}
	}
	return (myCoveredCities == cities);
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result){
	/* base cases */ 
	if(cities.size() <= 0) return true;
	if(cities.size() > 0 && locations.size() <= 0) return false;
	if(numHospitals <= 0 && cities.size() > 0) return false;
	
	if(checkFinalAnswer(cities, result)) return true;

	// if result vector is the same size as numhospitals, it should return false
	// because that means, it didnt give us TRUE when it checked whether 
	// the cities were fully covered, meaning we have wrong set of hospitals
	if(result.size() == numHospitals) return false; 
	
	foreach(Set<string> curr in locations){
		result.add(curr);
		if(result.size() < numHospitals) result.add(curr);
		if(canOfferUniversalCoverage(cities, locations, numHospitals, result)) return true;
		else result.remove(result.size() - 1);
	}
	return false;
}

int main() {
    return 0;
}
