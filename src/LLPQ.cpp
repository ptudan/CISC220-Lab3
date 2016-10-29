/*
 * LLPQ.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: Paul
 */


#include "LLPQ.hpp"
#include "LLPQnode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

LLPQ::LLPQ(){
	first = NULL;
	last = NULL;
	size = 0;
}//LLPQ constructor

LLPQ::~LLPQ(){
	LLPQnode *tmp = first;
	while (first != NULL) {
		tmp = first->next;
		delete first;
		first = tmp;
		size --;
	}
	first = NULL;
	last = NULL;
}//LLPQ destructor

void LLPQ::printLLPQ(){
	// prints out the linked list/ priority queue
	LLPQnode *temp = first;
	while(temp != NULL){
		cout<<temp->data<<":"<<temp->freq<<"-> ";
		temp = temp->next;
	}//while
	cout<<endl;
}

void LLPQ::addFirst(char c, string code){
	//adds the very first character node to the linked list, along with an 
	//original default code value set to empty.
	first = new LLPQnode(c);
	first->code = "";
	last = first;
	size++;
}

void LLPQ::addAtFirst(char c, string code){
	// add a new node to the beginning of the linked list (modifying the first
	//pointer and the size, and setting the code field to the default = ""
	LLPQnode *temp = first;
	if(size == 0){
		addFirst(c, code);
		return;
	}//if
	else if(size == 1){
		first->prev = new LLPQnode(c);
		first = first->prev;
		first->next = temp;
		last = first->next;
		first->freq = 1;
		first->code = "";
		size++;
		return;
	}//else if
	
	temp = first;
	first = new LLPQnode(c);
	first->next = temp;
	first->code = "";
	first->freq = 1;
	temp->prev = first;
	size++;
}

LLPQnode* LLPQ::remFirst(){
	// removes the first node from the list (to be used in creating the
	//Huffman code
	if(size == 1){//if only node in list
		LLPQnode *temp = first;
		first = NULL;
		last = NULL;
		size--;
		return temp;
	}//if
	else if(size==2){//if size is 2 (and decreases to 1), makes sure last is set to first
		LLPQnode *temp = first;
		first->next->prev = NULL;
		first = first->next;
		size--;
		last = first;
		return temp;
	}//else if
	else{
		LLPQnode *temp = first;
		first = first->next;
		first->prev = NULL;
		size--;
		return temp;
	}//else
	
}

string LLPQ::findCode(char c){
	// goes through the linked list, finds the character c, and returns
	//the code associated with that node – used to translate a file once
	//you have the code (Note that if we had studied hash tables/maps, 
	//this would be so much easier using them
	LLPQnode *temp = first;
	for(int i = 0; i<size; i++){
		if(temp->data == c){
			return temp->code;
		}//if
		else{
			temp = temp->next;
		}//else
	}//for
	return "";
}//findCode

void LLPQ::sortLLPQ(){
	// sorts your linked list, based on the counts in the nodes (so 
	//the character that occurred the least frequently will be at the 
	//beginning of the list, and the character that occurred most 
	//frequently will be at the end of the list.
	LLPQnode *temp;
	bool isSorted;
	if(size == 1){
		return;
	}//if
	else if(size == 2){
		temp = first;
		if(first->data > last->data){//if first>last, switch the nodes and return
			first->next = NULL;
			first->prev = last;
			last->prev = NULL;
			last->next = first;
			first = last;
			last = temp;
		}//if
		return;
	}//else if
	for(int i = 0; i<size; i++){//standard bubble sort
		isSorted = true;
		temp = first;
		for(int j = 0; j<size-1; j++){
			if(temp==first && temp->freq > temp->next->freq){//if current node is bigger than next, swap
				isSorted = false;
				LLPQnode *temp2 = temp->next;
				temp2->prev = NULL;
				temp->prev = temp2;
				temp->next = temp2->next;
				temp2->next->prev = temp;
				temp2->next = temp;
				first = temp2;//special case when first node to keep track of first
			}//if
			else if(temp->freq > temp->next->freq){//if current node is bigger than next, swap
				isSorted = false;
				LLPQnode *temp2 = temp->next;
				if(temp2->next == NULL){//special case when comparing second to last and last node
					temp->next = NULL;
					last = temp;
				}//if
				else{
					temp->next = temp2->next;
					temp2->next->prev = temp;
				}//else
				temp2->prev = temp->prev;
				temp->prev->next = temp2;
				temp->prev = temp2;
				temp2->next = temp;
			}//else if
			else{
				temp = temp->next;
			}//else
		}//for
		if(isSorted){
			return;
		}//if
	}//for
}

void LLPQ::insertUnique(char c){
	// inserts only unique characters into the linked list. If the character 
	//is already in the linked list, it increases the count of that character
	LLPQnode *temp = first;
	for(int i = 0; i<size; i++){
		if(temp->data==c){//if data exists, increment
			temp->freq++;
			return;
		}//if
		temp = temp->next;
	}//for
	addAtFirst(c, "");//add at beginning if not already in LLPQ
}

void LLPQ::insertInOrder(LLPQnode *n){
	//inserts the node n into the linked list in order of its count value – 
	//this will be used in the creation of the Huffman code.
	if(size == 0){//special case when size == 0
		first = n;
		last = n;
		size = 1;
		return;
	}
	LLPQnode *temp = first;
	int freqPrev = 2143432143;
	for(int i = 0; i<size-1; i++){
		if(freqPrev<=n->freq && n->freq<=temp->freq){
			LLPQnode *temp2 = temp->prev;
			temp->prev = n;
			temp2->next = n;
			n->prev = temp2;
			n->next = temp;
			size++;
			return;
		}//if
		else{
			freqPrev = temp->freq;
			temp = temp->next;
		}//else
	}//for
	//cout<<"finished for "<<endl;
	temp->next = n;
	//cout<<"1"<<endl;
	n->prev = temp;
	last = n;
	size++;
}

void LLPQ::push(LLPQnode* n){
	if(size == 0){//special case when size is 0 to track first/last
		first = n;
		last = n;
		size = 1;
		return;
	}//if
	last->next = n;
	n->prev = last;
	last = n;
	last->next = NULL;
	size++;
}

