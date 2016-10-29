/*
 * LLPQ.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: Paul
 */


#include "LLPQ.hpp"
#include "LLPQnode.hpp"
#include "LLHuff.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <direct.h>
#include <windows.h>
#include "LLPQ.hpp"
#include "LLPQnode.hpp"
using namespace std;


LLHuff::LLHuff(string f) {
	file = f;
	pq = new LLPQ;
	ascii = new LLPQ;
	size = 0;
}

LLHuff::~LLHuff() {
	delete pq;
	delete ascii;
	delete root;
}

void LLHuff::MakeHuff() {
	//takes the priority queue and makes the Huffman tree out of it as 
	//shown above, setting the root to the last remaining node created.
	LLPQnode *temp = new LLPQnode('*');
	size+= pq->size;//sets size correctly (though unused)
	//int iteration = 0;
	while(pq->size > 1){//until root is found
		//iteration++;
		//cout<<"iteration "<< iteration<<endl;
		temp = new LLPQnode('*');
		temp->freq = pq->first->getFreq() + pq->first->next->getFreq();//sets freq of new node with 1st +2nd freqs
		temp->left = pq->remFirst();//sets left child to first node in pq
		temp->right = pq->remFirst();//sets right child to second node in pq
		pq->insertInOrder(temp);
		size++;
		//pq->printLLPQ();
		
	}//while
	root = temp;
	
	
}

void LLHuff::FindCode(LLPQnode* root, string path) {
	//finds the code for each leaf node in the tree. A few notes about this one: 
	//first, the path starts at 1, and is multiplied by 10 each iteration through 
	//to get an accurate integer representation of the path. I wrote this function 
	//as a recursive one, and I STRONGLY recommend you do as well. All codes for 
	//every leaf can be found in one pass of the tree with recursion.
	if(root->left !=NULL){
		FindCode(root->left, path+"0");//if the left node isn't null, continue to find leaf
	}//if
	if(root->right != NULL){
		FindCode(root->right, path+"1");//if the right node isn't null, continue to find leaf
	}//if
	if(root->right == NULL && root->left == NULL){
		root->code = path;//sets code based on previous bounces when node has no children
		pq->push(root);//adds node with code onto pq
	}//if
}

void LLHuff::ReadFile() {
	//Opens, reads in a file character by character, and creates the priority queue
	ifstream infile(file.c_str(),ios::in); // open file
	char k;
	while (infile.get(k)) { // loop getting single characters
		pq->insertUnique(k);// inserting the character k into the priority queue
	}//while
	infile.close();
}


void LLHuff::compressFile() {
	////Opens the original file for reading and a new, compressed file for writing.
	//Looks up each character read in from the original file and writes out its
	//corresponding code in the compressed file.
	FindCode(root, "");//finds codes for nodes, recreates pq with nodes with codes
	ofstream compressed;
	compressed.open("compressed.txt");
	ifstream infile(file.c_str(),ios::in);
	char k;
	string comp;
	while (infile.get(k)){
		comp = pq->findCode(k);//finds code of char
		if(comp == ""){
			cout << "ERROR WITH " << k << endl;
		}//if
		else{
			cout << k << ":" << comp << endl; //shows char and code
			compressed << comp << " "; //prints to .txt file
		}//else
	}//while
	infile.close();
	compressed.close();
}//compressFile

void LLHuff::ReadAscii() {
	//reads in the asci code from the asci.txt file, and then takes the regular 
	//file and converts it to the ascii code and saves that file.
	cout << file << endl;
	ifstream infile("asciitable.txt",ios::in); // open file
	char ch;
	string asciicode;
	if (!infile.is_open()) {
		return;
	}
	infile >> asciicode;
	pq->addFirst(' ',asciicode);
	infile >> asciicode;
	
	while (infile>>ch) { // loop getting single characters
		cout << ch;
		infile>>asciicode; // gets entire word (code)
		cout << asciicode << endl;
		pq->addAtFirst(ch,asciicode);
	}
	cout << endl;
	infile.close();
	/////////////////////////////////////
	ifstream infile2(file.c_str(),ios::in); // open file for reading
	ofstream outfile("asciivsn.txt",ios::out);
	char k;
	string comp;
	while (infile2.get(k)) { // loop getting single characters
		comp = pq->findCode(k);
		if (comp == "") {
			cout << "ERROR WITH " << k << endl;
		}
		else {
			cout << k << ":" << comp << endl;
			outfile << comp << " ";
		}
	}
	cout << endl;
	infile2.close();
	outfile.close();
}
