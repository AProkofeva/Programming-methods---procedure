#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
// �������� ������ ��� ������ �� ������
enum type {USUAL, DIAGONAL};
struct dv_massiv 
{
	type key;
	int n;
	int **A; 
};
struct diagonal_matr
{
	type key;
	int n;
	int *A; 
};
struct matr 
{
    type key; // ����
};
struct container
{
   matr *cont;
   int len;
   struct container *next; // ��������� �� ��������� �������
   struct container *prev; // ��������� �� ���������� �������
};
void In_Mas(dv_massiv* &mas, ifstream &ifst);
void In_Diagonal(diagonal_matr* &mas,ifstream &ifst);
void Out_mas(dv_massiv* &mas, ofstream &ofst);
void Out_diagonal(diagonal_matr* &mas, ofstream &ofst);
int Sum_Diagonal(diagonal_matr* &mas);
int Sum_mas(dv_massiv* &mas);
int Sum(matr *mas);
matr* ReadM(ifstream& ifst);
void OutM(matr *mas, ofstream &ofst);
struct container * init();
void Clear(container* &c);
int In(container* &c, ifstream &ifst);
void Out(container* &c, ofstream &ofst);
void OutFirst(container* &c, ofstream &ofst);