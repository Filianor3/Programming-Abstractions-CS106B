#include "pqueue-heap.h"
#include "error.h"
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
	heapList = new string[8];
	sizee = 8;
	logicalSize = 0;
}

HeapPriorityQueue::~HeapPriorityQueue(){	
	delete[] heapList;
}

int HeapPriorityQueue::size(){
	return logicalSize;
}

bool HeapPriorityQueue::isEmpty(){
	return logicalSize == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(sizee == logicalSize){ 
		reWriteArray();
	}
	heapList[logicalSize] = value;
	logicalSize++;
	bubbleUp();
}

string HeapPriorityQueue::peek(){
	if(isEmpty()){
		error("Cant peek from an empty heap list");
	}
	return heapList[0];
}

string HeapPriorityQueue::dequeueMin(){
	if(isEmpty()){
		error("Cant dequeue from an empty heap list");
	}
	string answer = heapList[0];
	swap(heapList[0], heapList[logicalSize - 1]);
	logicalSize--;
	bubbleDown();
	return answer;
}

void HeapPriorityQueue::reWriteArray(){
	string* newHeapList = new string[logicalSize * 2];
	for(int i = 0; i < sizee; i++){
		newHeapList[i] = heapList[i];
	}
	delete[] heapList;
	heapList = newHeapList;
	sizee = logicalSize * 2;
}

void HeapPriorityQueue::bubbleUp(){
	int index = logicalSize - 1;	
	while(true){
		if(index == 0){
			break;
		}
		if(heapList[index] < heapList[(index - 1) / 2]){
			swap(heapList[index], heapList[(index - 1)/2]);
		}
		index = (index - 1) / 2;
	}
}

void HeapPriorityQueue::bubbleDown(){
	int index = 0;
	int minimum = 0;
	while(true){
		if(inBound(index * 2 + 1)){
			if(inBound((index + 1) * 2)){
				if(heapList[(index + 1) * 2] < heapList[index * 2 + 1]){
					minimum = (index + 1) * 2;
				}else{
					minimum = (index * 2 + 1);
				}
			}else {
				minimum = index * 2 + 1;
			}
		}else{
			break;
		}
		if(heapList[index] > heapList[minimum]){
			swap(heapList[index], heapList[minimum]);
			index = minimum;
		}else{
			break;
		}
	}
}

bool HeapPriorityQueue::inBound(int index){
	return (index >= 0 && index < logicalSize);
}