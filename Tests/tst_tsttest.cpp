#include <QString>
#include <QtTest>
#include "def.h"
class TstTest : public QObject
{
    Q_OBJECT

public:
    TstTest();

private Q_SLOTS:
    void testMas_data();
    void testMas();
    void testDiagonal_data();
    void testDiagonal();
    void testTriangle_data();
    void testTriangle();
    void testCompare_data();
    void testCompare();
	void testInit();
    void testInDiagonal();
    void testInTriangle();
    void testInMas();
    void testIn();
    void testInEmpty();
    void testInOne();
    void testOut();
    void testOne();
    void testEmpty();
    void sortEmpty();
    void sortOne();
    void sortList();
    void sortAssorted();
    void sortSort();
    void testClear();
};

TstTest::TstTest()
{
}
//Тест на сумму двумерного массива
void TstTest::testMas_data()
{
    QTest::addColumn<int>("size");
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("expected");

    QTest::newRow("compare01") << 0 << 0 << 0;
    QTest::newRow("compare02") << 1 << 10 << 10;
    QTest::newRow("compare03") << 3 << 15 << 171;
    QTest::newRow("compare04") << 5 << 10 << 550;
    QTest::newRow("compare05") << 10 << 1 << 5050;
}

void TstTest::testMas()
{
    QFETCH(int, size);
    QFETCH(int, first);
    QFETCH(int, expected);
	_squareMatr *mas;
	mas = new _squareMatr;
    mas->n = size;
    mas->A = new int*[mas->n];
    for (int i = 0; i <mas->n; ++i)
    {
        mas->A[i]=new int[mas->n];
    }
    int k = 0;
    for (int i = 0; i <mas->n; ++i)
    {
        for(int j = 0; j<mas->n; ++j)
        {
            mas->A[i][j]= first + k;//mas2[i][j];
            k++;
        }
    }
	int actual = SumSquare(mas);
    QCOMPARE(actual, expected);
}
//Тест на сумму диагональной матрицы
void TstTest::testDiagonal_data()
{
    QTest::addColumn<int>("size");
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("expected");

    QTest::newRow("compare01") << 0 << 0 << 0;
    QTest::newRow("compare02") << 1 << 10 << 10;
    QTest::newRow("compare03") << 3 << 15 << 48;
    QTest::newRow("compare04") << 10 << 10 << 145;
    QTest::newRow("compare05") << 100 << 1 << 5050;
}
void TstTest::testDiagonal()
{
    QFETCH(int, size);
    QFETCH(int, first);
    QFETCH(int, expected);
	_diagonalMatr *mas;
	mas = new _diagonalMatr;
    mas->n = size;
    mas->A = new int[mas->n];
    int k = 0;
    for (int i = 0; i <mas->n; ++i)
    {
		mas->A[i] = first + k;
        k++;
    }
	int actual = SumDiagonal(mas);
    QCOMPARE(actual, expected);
}
//Тест на сумму двумерного массива
void TstTest::testTriangle_data()
{
    QTest::addColumn<int>("size");
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("expected");

    QTest::newRow("compare01") << 0 << 0 << 0;
    QTest::newRow("compare02") << 1 << 10 << 10;
    QTest::newRow("compare03") << 7 << -2 << 7;
    QTest::newRow("compare04") << 10 << 10 << 145;
    QTest::newRow("compare05") << 100 << 1 << 5050;
}
void TstTest::testTriangle()
{
    QFETCH(int, size);
    QFETCH(int, first);
    QFETCH(int, expected);
	_triangleMatr *mas;
	mas = new _triangleMatr;
    mas->n = size;
    mas->A = new int[mas->n];
    int k = 0;
    for (int i = 0; i <mas->n; ++i)
    {
		mas->A[i] = first + k;
        k++;
    }
	int actual = SumTriangle(mas);
    QCOMPARE(actual, expected);
}
// Тест функции сранения
void TstTest::testCompare_data()
{
    QTest::addColumn<int>("size_usual");
    QTest::addColumn<int>("size_diagonal");
    QTest::addColumn<int>("size_triangle");
    QTest::addColumn<bool>("expected");
    QTest::newRow("compare01") << 0 << 0 << 0 << false;
    QTest::newRow("compare02") << 1 << 1 << 1 << false;
    QTest::newRow("compare03") << 3 << 3 << 3 << true;
    QTest::newRow("compare04") << 20 << 20 << 20 << true;
}
void TstTest::testCompare()
{
    QFETCH(int, size_usual);
    QFETCH(int, size_diagonal);
    QFETCH(int, size_triangle);
    QFETCH(bool, expected);
	_matr * matrM;
	_matr * matrT;
	_matr * matrD;
	matrM = new _matr;
	matrT = new _matr;
	matrD = new _matr;

	_squareMatr *square;
	square = new _squareMatr;
    square->key = USUAL;

	_diagonalMatr *diag;
	diag = new _diagonalMatr;
    diag->key = DIAGONAL;

	_triangleMatr *tri;
	tri = new _triangleMatr;
    tri->key = TRIANGLE;

    square->n = size_usual;
    square->A = new int*[square->n];
    for (int i = 0; i <square->n; ++i)
    {
        square->A[i]=new int[square->n];
    }
    for (int i = 0; i <square->n; ++i)
    {
        for (int j = 0; j <square->n; ++j)
        {
            square->A[i][j] = 1;
        }
    }
    tri->n = size_triangle;
    tri->A = new int [tri->n];
    for (int i = 0; i <tri->n; ++i)
    {
        tri->A[i] = 1;
    }
    diag->n = size_diagonal;
    diag->A = new int [diag->n];
    for (int i = 0; i <diag->n; ++i)
    {
        diag->A[i] = 1;
    }
	matrM = (_matr*)square;
	matrT = (_matr*)tri;
	matrD = (_matr*)diag;
    bool actual =  Compare(matrM, matrT);
    QCOMPARE(actual, expected);
    bool actual2 =  Compare(matrM, matrM);
    bool expected2 = false;
    QCOMPARE(actual2, expected2);
    bool actual3 =  Compare(matrD, matrT);
    bool expected3 = false;
    QCOMPARE(actual3, expected3);
}
void TstTest::testInit()
{
	_container *c;
	c = Init();
    int actualLen = c->len;
    int expectedLen = 0;
    QCOMPARE(actualLen, expectedLen);
	_matr* actual = c->cont;
	_matr* expected = NULL;
    QCOMPARE(actual, expected);
	_container* actual1 = c->prev;
	_container* expected1 = NULL;
    QCOMPARE(actual1, expected1);
	_container* actual2 = c->next;
	_container* expected2 = NULL;
    QCOMPARE(actual2, expected2);
}
void TstTest::testInDiagonal()
{
    FILE *fp = fopen("in_diagonal.txt","r");
    ifstream ifst(fp);
	_matr * temp = ReadMas(ifst);
	_diagonalMatr *actualHead;
	actualHead = (_diagonalMatr*)temp;
	_diagonalMatr *expectedHead;
	expectedHead = new _diagonalMatr;
    expectedHead->key =DIAGONAL;
	expectedHead->outway = ONE_MASSIV;
    expectedHead->n = 3;
    expectedHead->A = new int[expectedHead->n];
    int mas2[3] = {4, 3, 5};
    for (int i = 0; i <expectedHead->n; ++i)
    {
        expectedHead->A[i]= mas2[i];
    }
    for (int i = 0; i< expectedHead->n; ++i)
    {
        QCOMPARE(actualHead->A[i], expectedHead->A[i]);
    }
    fclose(fp);
}
void TstTest::testInMas()
{
    FILE *fp = fopen("in_mas.txt","r");
    ifstream ifst(fp);
	_matr * temp = ReadMas(ifst);
	_squareMatr *actualHead;
	actualHead = (_squareMatr*)temp;
	_squareMatr *expectedHead;
	expectedHead = new _squareMatr;
    expectedHead->key =USUAL;
	expectedHead->outway = LINE_BY_LINE;
    expectedHead->n = 3;
    expectedHead->A = new int*[expectedHead->n];
    for (int i = 0; i < expectedHead->n; i++)
    {
        expectedHead->A[i] = new int[expectedHead->n];
    }
    int mas2[3][3]={{12,45,78},
                    {23,56,89},
                    {87,54,21}};
    for (int i = 0; i <expectedHead->n; ++i)
    {
        for (int j =0; j< expectedHead->n; ++j)
        {
            expectedHead->A[i][j]= mas2[i][j];
        }
    }
    for (int i = 0; i< expectedHead->n; ++i)
    {
        for (int j = 0; j <expectedHead->n; ++j)
        {
            QCOMPARE(actualHead->A[i][j], expectedHead->A[i][j]);
        }
    }
    fclose(fp);
}
void TstTest::testInTriangle()
{
    FILE *fp = fopen("in_triangle.txt","r");
    ifstream ifst(fp);
	_matr * temp = ReadMas(ifst);
	_triangleMatr *actualHead;
	actualHead = (_triangleMatr*)temp;
	_triangleMatr *expectedHead;
	expectedHead = new _triangleMatr;
    expectedHead->key =TRIANGLE;
	expectedHead->outway = ONE_MASSIV;
    expectedHead->n = 6;
    expectedHead->A = new int[expectedHead->n];
    int mas2[6] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i <expectedHead->n; ++i)
    {
        expectedHead->A[i]= mas2[i];
    }
    for (int i = 0; i< expectedHead->n; ++i)
    {
        QCOMPARE(actualHead->A[i], expectedHead->A[i]);
    }
    fclose(fp);
}
void TstTest::testIn()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in1.txt","r");
    ifstream ifst(fp);
    int actuallen = In(c, ifst);
    int expectedlen = 5;
    QCOMPARE(actuallen, expectedlen);
	_container *p;
    p = c;
    type expected[5] = {TRIANGLE, USUAL, DIAGONAL,DIAGONAL,TRIANGLE};
    for( int i = 0; i < actuallen-1; i++)
            p = p ->prev;
    int count = 0;
    while (p != NULL)
    {
		_matr* actual = p->cont;
        QCOMPARE(actual->key, expected[count]);
        count++;
        p = p->next;
    }
    fclose(fp);
}
void TstTest::testInEmpty()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in_empty.txt","r");
    ifstream ifst(fp);
    int actuallen = In(c, ifst);
    int expectedlen = 0;
    QCOMPARE(actuallen, expectedlen);
	_matr* actual = c->cont;
	_matr* expected = NULL;
    QCOMPARE(actual, expected);
	_container* actual1 = c->prev;
	_container* expected1 = NULL;
    QCOMPARE(actual1, expected1);
	_container* actual2 = c->next;
	_container* expected2 = NULL;
    QCOMPARE(actual2, expected2);
    fclose(fp);
}
void TstTest::testInOne()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in_one.txt","r");
    ifstream ifst(fp);
    int actuallen = In(c, ifst);
    int expectedlen = 1;
    QCOMPARE(actuallen, expectedlen);
    type expected = USUAL;
	_matr* actual = c->cont;
    QCOMPARE(actual->key, expected);
    fclose(fp);
}
void TstTest::testOut()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in.txt","r");
    ifstream ifst(fp);
    FILE *fn = fopen("out.txt","w");
    ofstream ofst(fn);
    int actuallen = In(c, ifst);
    Out(c, ofst);
    fclose(fn);
    fclose(fp);
    FILE *fd = fopen("out.txt","r");
    ifstream actual(fd);
    FILE *fk = fopen("outexp.txt","r");
    ifstream expected(fk);
    char act;
    char exp;
    while(!actual.eof())
    {
        actual >> act;
        expected >> exp;
        QCOMPARE(act, exp);
    }
    fclose(fd);
    fclose(fk);
}
void TstTest::testEmpty()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in_empty.txt","r");
    ifstream ifst(fp);
    FILE *fn = fopen("outemp.txt","w");
    ofstream ofst(fn);
    int actuallen = In(c, ifst);
    Out(c, ofst);
    fclose(fn);
    fclose(fp);
    FILE *fd = fopen("outemp.txt","r");
    ifstream actual(fd);
    FILE *fk = fopen("out_empty.txt","r");
    ifstream expected(fk);
    char act;
    char exp;
    while(!actual.eof())
    {
        actual >> act;
        expected >> exp;
        QCOMPARE(act, exp);
    }
    fclose(fd);
    fclose(fk);
}
void TstTest::testOne()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in_one.txt","r");
    ifstream ifst(fp);
    FILE *fn = fopen("out1.txt","w");
    ofstream ofst(fn);
    int actuallen = In(c, ifst);
    Out(c, ofst);
    fclose(fn);
    fclose(fp);
    FILE *fd = fopen("out1.txt","r");
    ifstream actual(fd);
    FILE *fk = fopen("out_one.txt","r");
    ifstream expected(fk);
    char act;
    char exp;
    while(!actual.eof())
    {
        actual >> act;
        expected >> exp;
        QCOMPARE(act, exp);
    }
    fclose(fd);
    fclose(fk);
}
void TstTest::sortEmpty()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in_empty.txt","r");
    ifstream ifst(fp);
    FILE *fn = fopen("sortemp.txt","w");
    ofstream ofst(fn);
    int actuallen = In(c, ifst);
    Sort(c,actuallen);
    Out(c, ofst);
    fclose(fn);
    fclose(fp);
    FILE *fd = fopen("sortemp.txt","r");
    ifstream actual(fd);
    FILE *fk = fopen("exp_sort_empty.txt","r");
    ifstream expected(fk);
    char act;
    char exp;
    while(!actual.eof())
    {
        actual >> act;
        expected >> exp;
        QCOMPARE(act, exp);
    }
    fclose(fd);
    fclose(fk);
}
void TstTest::sortOne()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in_one.txt","r");
    ifstream ifst(fp);
    FILE *fn = fopen("sortone.txt","w");
    ofstream ofst(fn);
    int actuallen = In(c, ifst);
    Sort(c,actuallen);
    Out(c, ofst);
    fclose(fn);
    fclose(fp);
    FILE *fd = fopen("sortone.txt","r");
    ifstream actual(fd);
    FILE *fk = fopen("exp_sort_one.txt","r");
    ifstream expected(fk);
    char act;
    char exp;
    while(!actual.eof())
    {
        actual >> act;
        expected >> exp;
        QCOMPARE(act, exp);
    }
    fclose(fd);
    fclose(fk);
}
void TstTest::sortList()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in.txt","r");
    ifstream ifst(fp);
    FILE *fn = fopen("sort_usual.txt","w");
    ofstream ofst(fn);
    int actuallen = In(c, ifst);
    Sort(c,actuallen);
    Out(c, ofst);
    fclose(fn);
    fclose(fp);
    FILE *fd = fopen("sort_usual.txt","r");
    ifstream actual(fd);
    FILE *fk = fopen("exp_sort_usual.txt","r");
    ifstream expected(fk);
    char act;
    char exp;
    while(!actual.eof())
    {
        actual >> act;
        expected >> exp;
        QCOMPARE(act, exp);
    }
    fclose(fd);
    fclose(fk);
}
void TstTest::sortAssorted()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in_assort.txt","r");
    ifstream ifst(fp);
    FILE *fn = fopen("sort_assort.txt","w");
    ofstream ofst(fn);
    int actuallen = In(c, ifst);
    Sort(c,actuallen);
    Out(c, ofst);
    fclose(fn);
    fclose(fp);
    FILE *fd = fopen("sort_assort.txt","r");
    ifstream actual(fd);
    FILE *fk = fopen("exp_sort_assort.txt","r");
    ifstream expected(fk);
    char act;
    char exp;
    while(!actual.eof())
    {
        actual >> act;
        expected >> exp;
        QCOMPARE(act, exp);
    }
    fclose(fd);
    fclose(fk);
}
void TstTest::sortSort()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in2.txt","r");
    ifstream ifst(fp);
    FILE *fn = fopen("sort_sort.txt","w");
    ofstream ofst(fn);
    int actuallen = In(c, ifst);
    Sort(c,actuallen);
    Out(c, ofst);
    fclose(fn);
    fclose(fp);
    FILE *fd = fopen("sort_sort.txt","r");
    ifstream actual(fd);
    FILE *fk = fopen("exp_sort_sort.txt","r");
    ifstream expected(fk);
    char act;
    char exp;
    while(!actual.eof())
    {
        actual >> act;
        expected >> exp;
        QCOMPARE(act, exp);
    }
    fclose(fd);
    fclose(fk);
}
void TstTest::testClear()
{
	_container *c;
	c = Init();
    FILE *fp = fopen("in2.txt","r");
    ifstream ifst(fp);
    int actuallen = In(c, ifst);
    Clear(c);
    int actualLen = c->len;
    int expectedLen = 0;
    QCOMPARE(actualLen, expectedLen);
	_matr* actual = c->cont;
	_matr* expected = NULL;
    QCOMPARE(actual, expected);
	_container* actual1 = c->prev;
	_container* expected1 = NULL;
    QCOMPARE(actual1, expected1);
	_container* actual2 = c->next;
	_container* expected2 = NULL;
    QCOMPARE(actual2, expected2);
}
QTEST_APPLESS_MAIN(TstTest)

#include "tst_tsttest.moc"
