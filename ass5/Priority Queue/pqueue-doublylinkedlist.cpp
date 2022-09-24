#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	sizee = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Node* curr; 
	while(true){
		if(head == NULL || head->next == NULL){
			break;
		}
		curr = head;
		head = head->next;
		delete curr;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return sizee;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return sizee == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* toAdd = new Node();
	toAdd->prev = NULL;
	toAdd->value = value;
	toAdd->next = head;
	if(head != NULL){
		head->prev = toAdd;
	}
	head = toAdd;
	sizee++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("Cant peek in an empty priority queue");
	}
	Node* curr = head;
	string answer = curr->value;
	while(true){
		if(curr == NULL || curr->next == NULL){
			break;
		}
		if(curr->next->value < answer){
			answer = curr->next->value;
		}
		curr = curr->next;
	}
	return answer;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("Cant dequeue in an empty priority queue");
	}
	if(sizee == 1){
		string answer = head->value;
		delete head;
		head = NULL;
		sizee--;
		return answer;
	}
	Node* toReturn = head;
	Node* curr = head;
	string answer = curr->value;
	while(true){
		if(curr == NULL || curr->next == NULL){
			break;
		}
		if(curr->next->value < answer){
			answer = curr->next->value;
			toReturn = curr->next;
		}
		curr = curr->next;
	}
	if(toReturn == head){
		head = head->next;
	}
	if(toReturn->prev != NULL){
		toReturn->prev->next = toReturn->next;	
	}
	if(toReturn->next != NULL){
		toReturn->next->prev = toReturn->prev;
	}
	sizee--;
	delete toReturn;
	return answer;
}

