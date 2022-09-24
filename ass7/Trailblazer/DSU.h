#pragma once
#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "map.h"

class DSU{
	
public:
	DSU();
	~DSU();
	void makeSet(Loc loc);
	void unionSet(Loc loc1, Loc loc2);
	Loc findSet(Loc loc);
	bool isSame(Loc loc1, Loc loc2);
private:
	Map<Loc, Loc> ourMap;
};
