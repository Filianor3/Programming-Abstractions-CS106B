#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
#include <limits>
#include "DSU.h"
using namespace std;

const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
const string COLOR_YELLOW = "YELLOW";
const string COLOR_GREEN = "GREEN";
const string COLOR_GREY = "GREY";
const int DIRECTIONS = 8;
const int minRand = 1;
const int maxRand = 20;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {
	Vector<Loc> answer; // creating the vector we will return
	
	// initialising grid which consists of our struct objects
	Grid<MyLoc>grid(world.nRows, world.nCols);
	makeEverythingGrey(grid);
	grid[start.row][start.col].color = COLOR_YELLOW;
	grid[start.row][start.col].distance = (double)0;

	//grid[start.row][start.col].parentLoc = NULL;
	
	// creating the starter form of the priority queue
	TrailblazerPQueue<Loc> q;
	q.enqueue(start, 0);
	
	// main part
	while(true){
		if(q.isEmpty()) break;
		Loc curr = q.dequeueMin(); // dequeueing the minimum priority element
		if(curr == end) break; // breaking if we reached the destination
		colorCell(world, curr, GREEN); // graphics part
		grid[curr.row][curr.col].color = COLOR_GREEN; 
		// iterating through all 8 directions of the current cell
		for(int i = 0; i < DIRECTIONS; i++){
			Loc v = makeLoc(curr.row + dx[i], curr.col + dy[i]);
			if(world.inBounds(v.row, v.col) && v != curr &&
				costFn(curr, v, world) < numeric_limits<double>::infinity()){ // inbound and the same sell checker
				// if grey
				if(grid[v.row][v.col].color == COLOR_GREY){
					colorCell(world, v, YELLOW);
					grid[v.row][v.col].color = COLOR_YELLOW;
					grid[v.row][v.col].parentLoc = curr;
					grid[v.row][v.col].distance = grid[curr.row][curr.col].distance + costFn(curr, v, world);
					q.enqueue(v, grid[v.row][v.col].distance + heuristic(v, end, world));
				}
				// if yellow 
				if(grid[v.row][v.col].color == COLOR_YELLOW){
					if(grid[v.row][v.col].distance > grid[curr.row][curr.col].distance + costFn(curr, v, world)){
						grid[v.row][v.col].distance = grid[curr.row][curr.col].distance + costFn(curr, v, world);
						grid[v.row][v.col].parentLoc = curr;
						q.decreaseKey(v, grid[v.row][v.col].distance + heuristic(v, end, world));
					}
				}

			}
		}
	}
	
	// adding the path in our answer vector
	while(true){
		if(end == start) break;
		answer.insert(0, end);
		end = grid[end.row][end.col].parentLoc;
	}
	answer.insert(0, start); // inserting the first node 
	
	return answer;
}

/* makes every grid's object's color grey */
void makeEverythingGrey(Grid<MyLoc> &grid){
	for(int i = 0; i < grid.nRows; i++){
		for(int j = 0; j < grid.nCols; j++){
			grid[i][j].color = COLOR_GREY;
		}
	}
}

Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> result;
	DSU clusters;
	TrailblazerPQueue<Edge> q;
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			clusters.makeSet(makeLoc(i, j));
			if(i  + 1 < numRows){
				Loc n = makeLoc(i, j);
				Loc s = makeLoc(i + 1, j);
				Edge tmp = makeEdge(n, s);
				q.enqueue(tmp, randomInteger(minRand, maxRand));
			}
			if(j + 1 < numCols){
				Loc w = makeLoc(i, j);
				Loc e = makeLoc(i, j + 1);
				Edge tmp = makeEdge(w, e);
				q.enqueue(tmp, randomInteger(minRand, maxRand));
			}
		}
	}
	
	while(!q.isEmpty()){
		Edge e = q.dequeueMin();
		Loc tmp1 = e.start;
		Loc tmp2 = e.end;
		if(!clusters.isSame(tmp1, tmp2)){
			clusters.unionSet(tmp1, tmp2);
			result.add(e);
		}
	}

	return result;
}


