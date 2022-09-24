#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	
}

VectorPriorityQueue::~VectorPriorityQueue() {
	
}

int VectorPriorityQueue::size() {
	return tmp.size();
}

bool VectorPriorityQueue::isEmpty() {
	return tmp.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	tmp.add(value);
}

string VectorPriorityQueue::peek() {
	string toReturn;
	if(tmp.isEmpty()){
		error("Your priority queue is empty!");
	}else{
		toReturn = tmp[0];
		foreach(string curr in tmp){
			if(curr < toReturn){
				toReturn = curr;
			}		
		}
	}
	return toReturn;
}

string VectorPriorityQueue::dequeueMin() {
	string toReturn;
	if(tmp.isEmpty()){
		error("Your priority queue is empty!");
	}else{
		toReturn = tmp[0];
		int index = 0;
		for(int i = 0; i < tmp.size(); i++){
			if(tmp[i] < toReturn){
				toReturn = tmp[i];
				index = i;
			}
		}
		tmp.remove(index);
	}
	return toReturn;
}

