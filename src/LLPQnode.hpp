/*
 * LLPQnode.hpp
 *
 *  Created on: Oct 19, 2016
 *      Author: Paul
 */

#ifndef LLPQNODE_HPP_
#define LLPQNODE_HPP_
#include <iostream>
#include <stdlib.h>
using namespace std;

class LLPQnode{
	friend class LLPQ;
	friend class LLHuff;
	char data;
	LLPQnode *next;
	LLPQnode *prev;
	LLPQnode *left;
	LLPQnode *right;
	int freq;
	string code;

	public:
		LLPQnode(char c);
		~LLPQnode();
		char getData();
		int getFreq();
		string getCode();
};




#endif /* LLPQNODE_HPP_ */
