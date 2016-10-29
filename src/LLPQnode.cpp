/*
 * LLPQnode.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: Paul
 */


#include "LLPQnode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

LLPQnode::LLPQnode(char c){
	data = c;
	next = NULL;
	prev = NULL;
	right = NULL;
	left = NULL;
	freq = 1;
}

LLPQnode::~LLPQnode(){
	cout<<"deleting node holding: "<< data<<endl;
}

char LLPQnode::getData(){
	return data;
}

int LLPQnode::getFreq(){
	return freq;
}

string LLPQnode::getCode(){
	return code;
}


