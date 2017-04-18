//#include "stdafx.h"
#include "def.h"

void CheckIn(ifstream &inFile)
{
	if(!inFile)
	{
		cout << "No input file found!" << endl;
		exit(1);
	}
}
void CheckOut(ofstream &outFile)
{
	if(!outFile)
	{
		cout << "No output file found!" << endl;
		exit(1);
	}
}
int CheckNumber(ifstream &inFile, int number)
{
	inFile >> number;
	if (inFile.fail())
    {
        cout << "Wrong input! Your file must contain only numbers!" << endl;
        exit(1);
    }
	if (( number < -1000 ) || (number > 1000))
	{
		 cout << "Wrong input! Your file contain large numbers!" << endl;
		 exit(1);
	}
	return number;
}
void CheckType(int number)
{
	int begin = 1;
	int end = 3;
	if (( number < begin ) || (number > end))
    {
        cout << "Wrong type!!! 1 - diagonal, 2 - square (usual), 3 - triangle matrix" << endl;
		cout << "OR  1 - line by line, 2 - by column, 3 - like one-dimensional way output of matrix" << endl;
        exit(1);
    }
}
void CheckSize(int size)
{
	if ((size < 2) || (size > 100))
    {
        cout << "Wrong size of matrix!!!" << endl;
        exit(1);
    }
}
void CheckTriangleSize(int size)
{
	float sq = sqrt(float(1 + 8*size));
	if ((sq - int(sq)) == 0)
	{
		float n = (-1 + sq)/2;
		if ((n - int(n)) == 0)
		{
			return ;
		}
		else
		{
			cout << "Wrong size of triangle matrix!!!" << endl;
			exit(1);
		}
	}
	else
	{
		cout << "Wrong size of triangle matrix!!!" << endl;
		exit(1);
	}
}
// значения ключей для каждой из матриц
void InSquare(_squareMatr* &mas, ifstream &inFile)
{
	mas->n = CheckNumber(inFile,mas->n);
	CheckSize(mas->n);
    mas->A = new int*[mas->n];
	for (int i = 0; i < mas->n; ++i)
	{
		mas->A[i]=new int[mas->n];
	}
	for( int i = 0; i < mas->n; i++)
	{
		for (int j = 0; j < mas->n; j++)
		{
			mas->A[i][j] = CheckNumber(inFile, mas->A[i][j]);
		}
	}
}
void InDiagonal(_diagonalMatr* &mas,ifstream &inFile)
{
	mas->n = CheckNumber(inFile,mas->n);
	CheckSize(mas->n);
	mas->A = new int [mas->n];
	for( int i = 0; i < mas->n; i++)
	{
		mas->A[i] = CheckNumber(inFile, mas->A[i]);
    }
}
void InTriangle(_triangleMatr* &mas,ifstream &inFile)
{
	mas->n = CheckNumber(inFile,mas->n);
	CheckSize(mas->n);
	CheckTriangleSize(mas->n);
    mas->A = new int [mas->n];
    for( int i = 0; i < mas->n; i++)
    {
		mas->A[i] = CheckNumber(inFile, mas->A[i]);
    }
}
void OutSquare(_squareMatr* &mas, ofstream &outFile)
{
	outFile << "It is a usual square matrix! Number of rows (columns) = " << mas->n << endl << "Matrix:" << endl;
    for (int i = 0; i < mas->n; i++)
    {
        for (int j = 0; j < mas->n; j++)
		{
			outFile << mas->A[i][j] << '\t';
		}
		outFile << endl;
    }
}
void OutDiagonal(_diagonalMatr* &mas, ofstream &outFile)
{
	outFile << "It is diagonal matrix! Number of rows (columns) = " << mas->n << endl << "Matrix:" << endl;
    for (int i = 0; i < mas->n; i++)
    {
        for (int j = 0; j < mas->n; j++)
		{
            if (i == j)
			{
				outFile << mas->A[i] << '\t';
			}
            else
			{
				outFile << "0\t";
			}
		}
		outFile << endl;
    }
}
void Out_triangle(_triangleMatr* &mas, ofstream &outFile)
{
	int n = ( -1 + sqrt(float(1 + 8 * mas->n)))/2;
	outFile << "It is low triangle matrix! Number of rows (columns) = " << n << endl << "Matrix:" << endl;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
		{
            if (i >= j)
            {
				outFile << mas->A[k] << '\t';
                k++;
            }
            else
			{
				outFile << "0\t";
			}
		}
		outFile << endl;
    }
}
_matr* ReadMas(ifstream& inFile)
{
	_matr *matrix = new _matr;
	_squareMatr *square;
	_diagonalMatr *diag;
	_triangleMatr *tri;
    int key = 0;
	key = CheckNumber(inFile,key);
	CheckType(key);
    int outmas = 0;
	outmas = CheckNumber(inFile,outmas);
	CheckType(outmas);
    switch (key)
    {
		case 1:
		{
            //matrix->key = DIAGONAL;
			diag = new _diagonalMatr;
            diag->key = DIAGONAL;
			InDiagonal(diag,inFile);
            switch (outmas)
            {
                case 1:
                {
					diag->outway = LINE_BY_LINE;
                    break;
                }
                case 2:
                {
					diag->outway = BY_COLUMN;
                    break;
                }
                case 3:
                {
					diag->outway = ONE_MASSIV;
                    break;
                }
                default:
				{
                    return 0;
				}
            }
			return (_matr*)diag;
        }

        case 2:
        {
			square = new _squareMatr;
            square->key = USUAL;
			InSquare(square,inFile);
            switch (outmas)
            {
                case 1:
                {
					square->outway = LINE_BY_LINE;
                    break;
                }
                case 2:
                {
					square->outway = BY_COLUMN;
                    break;
                }
                case 3:
                {
					square->outway = ONE_MASSIV;
                    break;
                }
                default:
				{
                    return 0;
				}
            }
			return (_matr*)square;
        }
        case 3:
        {
            //matrix->key = DIAGONAL;
			tri = new _triangleMatr;
            tri->key = TRIANGLE;
			InTriangle(tri,inFile);
            switch (outmas)
            {
                case 1:
                {
					tri->outway = LINE_BY_LINE;
                    break;
                }
                case 2:
                {
					tri->outway = BY_COLUMN;
                    break;
                }
                case 3:
                {
					tri->outway = ONE_MASSIV;
                    break;
                }
                default:
				{
                    return 0;
				}
            }
			return (_matr*)tri;
        }
        default:
		{
            return 0;
		}
    }
}
void OutMas(_matr *mas, ofstream &outFile)
{
	//_matr *matrix;
	_squareMatr *square;
	_diagonalMatr *diag;
	_triangleMatr *tri;
    switch(mas->key)
    {
        case USUAL:
        {
			square = (_squareMatr*)mas;
			switch(square->outway)
            {
                case LINE_BY_LINE:
                {
					outFile << "It is line by line method of output" << endl;
                    break;
                }
                case BY_COLUMN:
                {
					outFile << "It is method of output by columns" << endl;
                    break;
                }
                case ONE_MASSIV:
                {
					outFile << "It is method of output in shape of one-dimensional massiv" << endl;
                    break;
                }
                default:
                {
					outFile << "It is incorrect way of output matrix!" <<endl;
                    break;
                }
            }
			OutSquare(square,outFile);
            break;
        }
        case DIAGONAL:
        {
			diag = (_diagonalMatr*)mas;
			switch(diag->outway)
            {
                case LINE_BY_LINE:
                {
					outFile << "It is line by line method of output" << endl;
                    break;
                }
                case BY_COLUMN:
                {
					outFile << "It is method of output by columns" << endl;
                    break;
                }
                case ONE_MASSIV:
                {
					outFile << "It is method of output in shape of one-dimensional massiv" << endl;
                    break;
                }
                default:
                {
					outFile << "It is incorrect way of output matrix!" <<endl;
                    break;
                }
            }
			OutDiagonal(diag,outFile);
            break;
        }
        case TRIANGLE:
        {
			tri = (_triangleMatr*)mas;
			switch(tri->outway)
            {
                case LINE_BY_LINE:
                {
					outFile << "It is line by line method of output" << endl;
                    break;
                }
                case BY_COLUMN:
                {
					outFile << "It is method of output by columns" << endl;
                    break;
                }
                case ONE_MASSIV:
                {
					outFile << "It is method of output in shape of one-dimensional massiv" << endl;
                    break;
                }
                default:
                {
					outFile << "It is incorrect way of output matrix!" <<endl;
                    break;
                }
            }
			Out_triangle(tri,outFile);
            break;
        }
		default:
		{
			outFile << "It is incorrect matrix!" <<endl;
		}
    }
}
int SumDiagonal(_diagonalMatr* &mas)
{
    int sum = 0;
    for (int i = 0; i < mas->n; i++)
    {
        sum = sum + mas->A[i];
    }
    return sum;
}
int SumTriangle(_triangleMatr* &mas)
{
    int sum = 0;
    for (int i = 0; i < mas->n; i++)
    {
        sum = sum + mas->A[i];
    }
    return sum;
}
int SumSquare(_squareMatr* &mas)
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
int Sum(_matr *mas)
{
	_squareMatr *square;
	_diagonalMatr *diag;
	_triangleMatr *tri;
    switch(mas->key)
    {
        case USUAL:
        {
			square = (_squareMatr*)mas;
			int sum = SumSquare(square);
            return sum;
        }
        case DIAGONAL:
        {
			diag = (_diagonalMatr*)mas;
			int sum = SumDiagonal(diag);
            return sum;
        }
        case TRIANGLE:
        {
			tri = (_triangleMatr*)mas;
			int sum = SumTriangle(tri);
            return sum;
        }
        default:
		{
            return -1;
		}
    }
}
struct _container * Init()
{
	// а- значение первого узла
	struct _container *lst;
	// выделение пам¤ти под корень списка
	lst = new _container;
	lst->cont = NULL;
	lst->next = NULL; // указатель на следующий узел
	lst->len = 0;
	lst->prev = NULL; // указатель на предыдущий узел
	return(lst);
}

 //  ќчистка контейнера от элементов (освобождение пам¤ти)
void Clear(_container* &cont)
{
	while (cont->cont != NULL) //ѕока по адресу на начало списка что-то есть
    {
		_container *temp;
		temp = cont->prev;
        temp->next = NULL;
		delete cont; // освобождаем пам¤ть удал¤емого элемента
		cont = temp;
		//cont->len--;
    }
	//cont = NULL;
}
int In(_container* &cont, ifstream &inFile)
{
    int len = 0;
	len = CheckNumber(inFile,len);
	if (len < 0)
    {
        cout << "Wrong count of elements ( must be > 0)!!!" << endl;
        exit(1);
    }
	_container *cur;
	cur = cont;
	for(int i = 0; i < len; i++)
    {
		_matr *matrix;
		if((matrix = ReadMas(inFile))!=0)
        {
			_container *temp, *p;
			temp = new _container;
            p = cur->next; // сохранение указател¤ на следующий узел
            cur->next = temp; // предыдущий узел указывает на создаваемый
            temp->cont = matrix;
			temp->len = i + 1;// сохранение пол¤ данных добавл¤емого узла
            temp->next = p; // созданный узел указывает на следующий узел
            temp->prev = cur; // созданный узел указывает на предыдущий узел
			if (p != NULL)
			{
                p->prev = temp;
			}
            cur = temp;
        }
    }
	cont = cur;
    return len;
}
void Out(_container* &cont, ofstream &outFile)
{
	int len = cont->len;
	outFile << "Container contains " << len << " elements." << endl;
	if (cont->len == 0)
    {
        return;
    }
	_container *p;
	p = cont;
    for( int i = 0; i < len-1; i++)
	{
		p = p ->prev;
	}
    while (p != NULL)
    {
		outFile << p->len << ": "<<endl;
		OutMas(p->cont, outFile); // вывод значени¤ элемента p
        int sum = Sum (p->cont);
		outFile << "Sum of elements = " << sum << endl;
        p = p->next; // переход к следующему узлу
    }
}
bool Compare(_matr *mas1, _matr *mas2)
{
    int s = Sum(mas1);
    int sk = Sum(mas2);
    return (s>sk);
}
void Sort(_container* &cont, int len)
{
	_container *p;
	p = cont;
    bool flag;
    do
    {
        flag = false;
        for( int i = 0; i < len-1; i++)
		{
			p = p ->prev;
		}
        while (p->next != NULL)
        {
			_matr *one;
            one = p->cont;
            p = p->next;
			_matr *two;
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
			{
                p = p->prev;
			}
            p = p->next; // переход к следующему узлу
        }
	} while (flag);
}
void OutFirst(_container* &cont, ofstream &outFile)
{
	int len = cont->len;
    if (len == 0)
	{
        return;
	}
	_container *p;
	p = cont;
    for( int i = 0; i < len-1; i++)
	{
		p = p ->prev;
	}
    while (p != NULL)
    {
        if(p->cont->key == USUAL)
        {
			outFile << p->len << ": ";
			OutMas(p->cont, outFile); // вывод значени¤ элемента p
        }
        p = p->next; // переход к следующему узлу
    }
}
void Multimethod(_container* &cont, ofstream &outFile)
{
	int len = cont->len;
	if (cont->len == 0)
	{
		return;
	}
	_container *temp1;
	_container *temp2;
	temp1 = cont;
	for( int i = 0; i < len-1; i++)
			temp1 = temp1 ->prev;
	outFile << "--------------------------------------" <<endl;
	while (temp1 != NULL)
	{
		temp2 = temp1->next;
		while (temp2 != NULL)
		{
			switch(temp1->cont->key)
			{
				case USUAL:
				{
					switch(temp2->cont->key)
					{
						case USUAL:
						{
							outFile << "Usual matrix and usual matrix:" <<endl;
							break;
						}
						case DIAGONAL:
						{
							outFile << "Usual matrix and diagonal matrix:" <<endl;
							break;
						}
						case TRIANGLE:
						{
							outFile << "Usual matrix and triangle matrix:" <<endl;
							break;
						}
						default:
							outFile << "It is incorrect type matrix!" <<endl;
					}
					break;
				}
				case DIAGONAL:
				{
					switch(temp2->cont->key)
					{
						case USUAL:
						{
							outFile << "Diagonal matrix and usual matrix:" <<endl;
							break;
						}
						case DIAGONAL:
						{
							outFile << "Diagonal matrix and diagonal matrix:" <<endl;
							break;
						}
						case TRIANGLE:
						{
							outFile << "Diagonal matrix and triangle matrix:" <<endl;
							break;
						}
						default:
							outFile << "It is incorrect type matrix!" <<endl;
					}
					break;
				}
				case TRIANGLE:
				{
					switch(temp2->cont->key)
					{
						case USUAL:
						{
							outFile << "Triangle matrix and usual matrix:" <<endl;
							break;
						}
						case DIAGONAL:
						{
							outFile << "Triangle matrix and diagonal matrix:" <<endl;
							break;
						}
						case TRIANGLE:
						{
							outFile << "Triangle matrix and triangle matrix:" <<endl;
							break;
						}
						default:
							outFile << "It is incorrect type matrix!" <<endl;
					}
					break;
				}
				default:
					outFile << "It is incorrect type matrix!" <<endl;
			}
			OutMas(temp1->cont, outFile);
			OutMas(temp2->cont, outFile);
			outFile << "--------------------------------------" <<endl;
			temp2 = temp2->next;
		}
		temp1 = temp1->next; // переход к следующему узлу
	}
}
