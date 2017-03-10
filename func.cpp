#include "stdafx.h"
#include "def.h"
// �������� ������ ��� ������ �� ������
void In_Mas(dv_massiv* &mas, ifstream &ifst) 
{
	ifst >> mas->n;
	mas->A = new int*[mas->n];
	for (int i = 0; i <mas->n; ++i)
	{
		mas->A[i]=new int[mas->n];
	}
	for( int i = 0; i < mas->n; i++)
	{
		for (int j = 0; j < mas->n; j++)
		{
			ifst >> mas->A[i][j];
		}
	}
} 
void In_Diagonal(diagonal_matr* &mas,ifstream &ifst) 
{
	ifst >> mas->n;
	mas->A = new int [mas->n];
	for( int i = 0; i < mas->n; i++)
	{
		ifst >> mas->A[i];
	}
}
void Out_mas(dv_massiv* &mas, ofstream &ofst)
{
	ofst << "It is a usual square matrix! Number of rows (columns) = " << mas->n << endl << "Matrix:" << endl;
	for (int i = 0; i < mas->n; i++)
	{
		for (int j = 0; j < mas->n; j++)
			ofst << mas->A[i][j] << '\t';
		ofst << endl;
	}
}
void Out_diagonal(diagonal_matr* &mas, ofstream &ofst)
{
	ofst << "It is diagonal matrix! Number of rows (columns) = " << mas->n << endl << "Matrix:" << endl;
	for (int i = 0; i < mas->n; i++)
	{
		for (int j = 0; j < mas->n; j++)
			if (i == j)
				ofst << mas->A[i] << '\t';
			else
				ofst << "0\t";
		ofst << endl;
	}
}

matr* ReadM(ifstream& ifst)
{
	matr *matrix = new matr;
	dv_massiv *square;
	diagonal_matr *diag;
	int key;
	ifst >> key;
	int outmas;
	ifst >> outmas;
	switch (key)
	{
		case 1:
		{
			//matrix->key = DIAGONAL;
			diag = new diagonal_matr;
			diag->key = DIAGONAL;
			In_Diagonal(diag,ifst);
			switch (outmas)
			{
				case 1:
				{
					diag->outm = LINE_BY_LINE;
					break;
				}
				case 2:
				{
					diag->outm = BY_COLUMN;
					break;
				}
				case 3:
				{
					diag->outm = ONE_MASSIV;
					break;
				}
				default:
					return 0;
			}
			return (matr*)diag;
		}
		
		case 2:
		{
			square = new dv_massiv;
			square->key = USUAL;
			In_Mas(square,ifst);
			switch (outmas)
			{
				case 1:
				{
					square->outm = LINE_BY_LINE;
					break;
				}
				case 2:
				{
					square->outm = BY_COLUMN;
					break;
				}
				case 3:
				{
					square->outm = ONE_MASSIV;
					break;
				}
				default:
					return 0;
			}
			return (matr*)square;
		}
		default:
			return 0;
	}
}
void OutM(matr *mas, ofstream &ofst)
{
	//matr *matrix;
	dv_massiv *square;
	diagonal_matr *diag;
	switch(mas->key)
	{
		case USUAL:
		{
			square = (dv_massiv*)mas;
			switch(square->outm)
			{
				case LINE_BY_LINE:
				{
					ofst << "It is line by line method of output" << endl;
					break;
				}
				case BY_COLUMN:
				{
					ofst << "It is method of output by columns" << endl;
					break;
				}
				case ONE_MASSIV:
				{
					ofst << "It is method of output in shape of one-dimensional massiv" << endl;
					break;
				}
				default:
				{
					ofst << "It is incorrect way of output matrix!" <<endl;
					break;
				}
			}
			Out_mas(square,ofst);
			break;
		}
		case DIAGONAL:
		{
			diag = (diagonal_matr*)mas;
			switch(diag->outm)
			{
				case LINE_BY_LINE:
				{
					ofst << "It is line by line method of output" << endl;
					break;
				}
				case BY_COLUMN:
				{
					ofst << "It is method of output by columns" << endl;
					break;
				}
				case ONE_MASSIV:
				{
					ofst << "It is method of output in shape of one-dimensional massiv" << endl;
					break;
				}
				default:
				{
					ofst << "It is incorrect way of output matrix!" <<endl;
					break;
				}
			}
			Out_diagonal(diag,ofst);
			break;
		}
		default:
			ofst << "It is incorrect matrix!" <<endl; 
	}
}
struct container * init() 
{ 
  // �- �������� ������� ����
  struct container *lst;
  // ��������� ������ ��� ������ ������
  lst = new container;
  lst->cont = NULL;
  lst->next = NULL; // ��������� �� ��������� ����
  lst->len = 0;
  lst->prev = NULL; // ��������� �� ���������� ����
  return(lst);
}

 //  ������� ���������� �� ��������� (������������ ������)
void Clear(container* &c) 
{
	while (c!=NULL) //���� �� ������ �� ������ ������ ���-�� ����
    {
		container *temp;
		temp = c->next;
		c->prev = NULL;
		delete c; // ����������� ������ ���������� ��������
		c = temp;
    }
}
int In(container* &c, ifstream &ifst)
{
	int len = 0;
	ifst >> len;
	container *cur;
	cur = c;
	for(int i = 0; i <len; i++)
	{
		matr *matrix;
		if((matrix = ReadM(ifst))!=0)
		{
			container *temp, *p;
			temp = new container;
			p = cur->next; // ���������� ��������� �� ��������� ����
			cur->next = temp; // ���������� ���� ��������� �� �����������
			temp->cont = matrix;
			temp->len = i;// ���������� ���� ������ ������������ ����
			temp->next = p; // ��������� ���� ��������� �� ��������� ����
			temp->prev = cur; // ��������� ���� ��������� �� ���������� ����
			if (p != NULL)
				p->prev = temp;
			cur = temp;
		}
	}
	c = cur;
	return len;
}
void Out(container* &c, ofstream &ofst, int len)
{
	ofst << "Container contains " << len << " elements." << endl;
	container *p;
	p = c;
	for( int i = 0; i < len-1; i++)
			p = p ->prev;
	while (p != NULL)
	{
		ofst << p->len+1 << ": "<<endl;
		OutM(p->cont, ofst); // ����� �������� �������� p
		p = p->next; // ������� � ���������� ����
	} 
}