#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "def.h"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc !=3)
	{
		cout << "Error! Incorrect command line! "
		"Waited: command infile outfile" << endl;
		exit(1);
	}
	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);
	//FILE *fp = fopen("in.txt","r");
	//ifstream inFile(fp);
	//FILE *fn = fopen("out.txt","w");
	//ofstream outFile(fn);
	CheckIn(inFile);
	CheckOut(outFile);
	cout << "Start"<< endl;
	_container *cont;
	cont = Init();
	int len = In(cont, inFile);
	outFile << "Filled container. " << endl;
	Out(cont, outFile);
	outFile << "Sorted container. " << endl;
	Sort(cont, len);
	Out(cont, outFile);
	outFile << "Only usual matrix. " << endl;
	OutFirst(cont,outFile);
	Clear(cont);
	outFile << "Empty container. " << endl;
	Out(cont, outFile);
	cout << "Stop"<< endl;
	return 0;
}
