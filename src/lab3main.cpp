#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "LLPQ.hpp"
#include "LLHuff.hpp"
#include "LLPQnode.hpp"
using namespace std;

int main() {//asfd
	cout << "reading file" << endl;
	LLHuff code("Monet.txt");
	code.ReadFile();
	code.pq->printLLPQ();
	cout<<endl;
	code.pq->sortLLPQ();
	code.pq->printLLPQ();
	cout<<endl;
	code.MakeHuff();
	code.compressFile();
	cout<<endl;
	//code.ReadAscii();
	return 0;
}
