#include "stdafx.h"
#include "def.h"
// значения ключей для каждой из матриц
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
	matr *matrix;
	dv_massiv *square;
	diagonal_matr *diag;
	int key;
	ifst >> key;
	switch (key)
	{
		case 1:
		{
			//matrix->key = DIAGONAL;
			diag = new diagonal_matr;
			diag->key = DIAGONAL;
			In_Diagonal(diag,ifst);
			return (matr*)diag;
		}
		
		case 2:
		{
			square = new dv_massiv;
			square->key = USUAL;
			In_Mas(square,ifst);
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
			Out_mas(square,ofst);
			break;
		}
		case DIAGONAL:
		{
			diag = (diagonal_matr*)mas;
			Out_diagonal(diag,ofst);
			break;
		}
		default:
			ofst << "It is incorrect matrix!" <<endl; 
	}
}
int Sum_Diagonal(diagonal_matr* &mas)
{
	int sum = 0;
	for (int i = 0; i < mas->n; i++)
	{
		sum = sum + mas->A[i];
	}
	return sum;
}
int Sum_mas(dv_massiv* &mas)
{
	int sum = 0;
	for( int i = 0; i < mas->n; i++)
	{
		for (int j = 0; j < mas->n; j++)
		{
			sum = sum + mas->A[i][j];
		}
	}
	return sum;
}
int Sum(matr *mas)
{
	dv_massiv *square;
	diagonal_matr *diag;
	switch(mas->key)
	{
		case USUAL:
		{
			square = (dv_massiv*)mas;
			int sum = Sum_mas(square);
			return sum;
		}
		case DIAGONAL:
		{
			diag = (diagonal_matr*)mas;
			int sum = Sum_Diagonal(diag);
			return sum;
		}
		default:
			return -1; 
	}
}
struct container * init() 
{ 
  // а- значение первого узла
  struct container *lst;
  // выделение памяти под корень списка
  lst = new container;
  lst->cont = NULL;
  lst->next = NULL; // указатель на следующий узел
  lst->len = 0;
  lst->prev = NULL; // указатель на предыдущий узел
  return(lst);
}

 //  Очистка контейнера от элементов (освобождение памяти)
void Clear(container* &c) 
{
	while (c!=NULL) //Пока по адресу на начало списка что-то есть
    {
		container *temp;
		temp = c->next;
		c->prev = NULL;
		delete c; // освобождаем память удаляемого элемента
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
			p = cur->next; // сохранение указателя на следующий узел
			cur->next = temp; // предыдущий узел указывает на создаваемый
			temp->cont = matrix;
			temp->len = i;// сохранение поля данных добавляемого узла
			temp->next = p; // созданный узел указывает на следующий узел
			temp->prev = cur; // созданный узел указывает на предыдущий узел
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
		ofst << p->len+1 << ": ";
		OutM(p->cont, ofst); // вывод значения элемента p
		int sum = Sum (p->cont);
		ofst << "Sum of elements = " << sum << endl;
		p = p->next; // переход к следующему узлу
	} 
}
bool Compare(matr *mas1, matr *mas2)
{
	int s = Sum(mas1);
	int sk = Sum(mas2);
	return (s>sk);
}
void Sort(container* &c, int len)
{
	container *p;
	p = c;
	bool flag;
	do
	{
		flag = false;
		for( int i = 0; i < len-1; i++)
				p = p ->prev;
		while (p->next != NULL)
		{
			matr *one;
			one = p->cont;
			p = p->next;
			matr *two;
			two = p->cont;
			bool k = Compare(one, two);
			if (k == true)
			{
				p->cont = one;
				p = p->prev;
				p->cont = two;
				flag = true;
			}
			else
				p = p->prev;
			p = p->next; // переход к следующему узлу
		}
	} while (flag);
}