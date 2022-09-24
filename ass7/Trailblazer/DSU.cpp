#include "DSU.h"

DSU::DSU(){
	
}

DSU::~DSU(){
	
}

void DSU::makeSet(Loc loc){
	ourMap[loc] = loc;
}

void DSU::unionSet(Loc loc1, Loc loc2){
	ourMap[findSet(loc1)] = findSet(loc2);
}

Loc DSU::findSet(Loc loc){
	Loc temp = loc;
	while(temp != ourMap[temp]){
		temp = ourMap[temp];
	}
	ourMap[loc] = temp;
	return temp;
}

bool DSU::isSame(Loc loc1, Loc loc2){
	return findSet(loc1) == findSet(loc2);	
}