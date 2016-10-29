/*
 * LLPQ.hpp
 *
 *  Created on: Oct 19, 2016
 *      Author: Paul
 */

#ifndef LLPQ_HPP_
#define LLPQ_HPP_

#include "LLPQnode.hpp"

class LLPQ{
	friend class LLHuff;
	LLPQnode *first;
	LLPQnode *last;
	int size;


public:
	LLPQ();
	~LLPQ();
	void printLLPQ();
	void addFirst(char c, string code);
	void addAtFirst(char c, string code);
	LLPQnode *remFirst();
	string findCode(char c);
	void sortLLPQ();
	void insertUnique(char c);
	void insertInOrder(LLPQnode *n);
	void push(LLPQnode* n);
};





#endif /* LLPQ_HPP_ */
