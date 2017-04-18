//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
// значения ключей для каждой из матриц
enum type {USUAL, DIAGONAL, TRIANGLE};
enum output {LINE_BY_LINE, BY_COLUMN, ONE_MASSIV};
struct _squareMatr
{
	type key;
	int n;
	int **A;
	output outway;
};
struct _diagonalMatr
{
	type key;
	int n;
	int *A;
	output outway;
};
struct _triangleMatr
{
	type key;
	int n;
	int *A;
	output outway;
};
struct _matr
{
	type key; // ключ
};
struct _container
{
	_matr *cont;
	int len;
	struct _container *next; // указатель на следующий элемент
	struct _container *prev; // указатель на предыдущий элемент
};
void CheckIn(ifstream &inFile);
void CheckOut(ofstream &outFile);
int CheckNumber(ifstream &inFile, int number);
void CheckType(int number);
void CheckSize(int size);
void CheckTriangleSize(int size);
void InSquare(_squareMatr* &mas, ifstream &inFile);
void InDiagonal(_diagonalMatr* &mas,ifstream &inFile);
void InTriangle(_triangleMatr* &mas,ifstream &inFile);
void OutSquare(_squareMatr* &mas, ofstream &outFile);
void OutDiagonal(_diagonalMatr* &mas, ofstream &outFile);
void OutTriangle(_triangleMatr* &mas,ifstream &inFile);
int Sum(_matr *mas);
int SumSquare(_squareMatr* &mas);
int SumTriangle(_triangleMatr* &mas);
int SumDiagonal(_diagonalMatr* &mas);
_matr* ReadMas(ifstream& inFile);
void OutMas(_matr *mas, ofstream &outFile);
struct _container *Init();
void Clear(_container* &cont);
int In(_container* &cont, ifstream &inFile);
void Sort(_container* &cont, int len);
void Out(_container* &cont, ofstream &outFile);
bool Compare(_matr *mas1, _matr *mas2);
void OutFirst(_container* &cont, ofstream &outFile);
void Multimethod(_container* &cont, ofstream &outFile);
