#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	sizee = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Node* curr; 
	while(true){
		if(head == NULL || head->node == NULL){
			break;
		}
		curr = head;
		head = head->node;
		delete curr;
	}
}

int LinkedListPriorityQueue::size() {
	return sizee;
}

bool LinkedListPriorityQueue::isEmpty() {
	return sizee == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	if(sizee == 0){
		head = new Node();
		head->value = value;
		head->node = NULL;
	}else{
		Node* temp = head;
		if(temp->value > value){
			Node* toAdd = new Node();
			toAdd->value = value;
			toAdd->node = temp;
			head = toAdd;
		}else{
			while(true){
				if(temp == NULL){
					break;
				}
				if(temp->node == NULL){
					Node* toAdd = new Node();
					toAdd->value = value;
					toAdd->node = NULL;
					temp->node = toAdd;
					break;
				}
				if(temp->node->value > value){
					Node* toAdd = new Node();
					toAdd->value = value;
					toAdd->node = temp->node;
					temp->node = toAdd;
					break;
				}else{
					temp = temp->node;
				}
			}
		}
		
	}
	sizee++;
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("Cant peek from empty Priority queue.");
	}
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("Cant peek from empty Priority queue.");
	}
	Node* temp = head;
	string answer = head->value;
	head = head->node;
	delete temp;
	sizee--;
	return answer;
}

