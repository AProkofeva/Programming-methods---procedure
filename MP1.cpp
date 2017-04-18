// MP1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "def.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	if(argc !=3)	
	{
		cout << "Error! Incorrect command line! "
		"Waited: command infile outfile" << endl;
		exit(1);
	}
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);
	//FILE *fp = fopen("in.txt","r");
	//ifstream ifst(fp);
	//FILE *fn = fopen("out.txt","w");
	//ofstream ofst(fn);
	cout << "Start"<< endl;
	container *c;
	c = init();
	int len = In(c, ifst);
    ofst << "Filled container. " << endl;
	Out(c, ofst, len);
	ofst << "Multimethod " << endl;
	Multimethod(c, ofst, len);
	Clear(c);
    ofst << "Empty container. " << endl;
	Out(c, ofst,0);
	cout << "Stop"<< endl;
	return 0;
}

