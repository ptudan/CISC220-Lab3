/*
 * LLHuff.hpp
 *
 *  Created on: Oct 21, 2016
 *      Author: Paul
 */

#ifndef LLHUFF_HPP_
#define LLHUFF_HPP_
#include <iostream>
#include <stdlib.h>
using namespace std;

class LLHuff {
	friend class LLPQnode;
	friend class LLPQ;
	string file;
	LLPQnode *root;
	int size;
	
public:
	LLPQ *pq;
	LLPQ *ascii;
	LLHuff(string f);
	~LLHuff();
	void MakeHuff();
	void FindCode(LLPQnode *root, string path);
	void ReadFile();
	void compressFile();
	void ReadAscii();
};




#endif /* LLHUFF_HPP_ */
