// Lab_7_1.cpp
// < Качмар Владислав >
// Лабораторна робота № 7.1. rec
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Варіант 0(12)
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo);
void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo);

void PrintRow(int** a, const int rowNo, const int colCount, int colNo);
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo);

void Change(int** a, const int col1, const int col2, const int rowCount, int rowNo);

void Sort(int** a, const int rowCount, const int colCount, int j0, int j1);

void CalcRow(int** a, const int rowNo, const int colCount, int colNo, int& S, int& k);
void CalcRows(int** a, const int rowCount, const int colCount, int rowNo, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));
    int Low = -21;
    int High = 24;
    int rowCount = 9;
    int colCount = 6;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    CreateRows(a, rowCount, colCount, Low, High, 0);
    PrintRows(a, rowCount, colCount, 0);

    Sort(a, rowCount, colCount, 0, 0);
    PrintRows(a, rowCount, colCount, 0);

    int S = 0;
    int k = 0;
    CalcRows(a, rowCount, colCount, 0, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    PrintRows(a, rowCount, colCount, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}

// Виведення матриці
void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

// Рекурсивна заміна епізоду (обмін стовпчиків)
void Change(int** a, const int col1, const int col2, const int rowCount, int rowNo)
{
    int tmp = a[rowNo][col1];
    a[rowNo][col1] = a[rowNo][col2];
    a[rowNo][col2] = tmp;

    if (rowNo < rowCount - 1)
        Change(a, col1, col2, rowCount, rowNo + 1);
}

// Рекурсивне сортування (бульбашка)
void Sort(int** a, const int rowCount, const int colCount, int j0, int j1)
{
    if ((a[0][j1] < a[0][j1 + 1])
        ||
        (a[0][j1] == a[0][j1 + 1] &&
            a[1][j1] < a[1][j1 + 1])
        ||
        (a[0][j1] == a[0][j1 + 1] &&
            a[1][j1] == a[1][j1 + 1] &&
            a[2][j1] > a[2][j1 + 1]))
    {
        Change(a, j1, j1 + 1, rowCount, 0);
    }

    if (j1 < colCount - j0 - 1 - 1)
        Sort(a, rowCount, colCount, j0, j1 + 1);
    else if (j0 < colCount - 1 - 1)
        Sort(a, rowCount, colCount, j0 + 1, 0);
}

// Обчислення та заміна нулями
void CalcRow(int** a, const int rowNo, const int colCount, int colNo, int& S, int& k)
{
    if (a[rowNo][colNo] >= 0 && a[rowNo][colNo] % 3 == 0)
    {
        S += a[rowNo][colNo];
        k++;
        a[rowNo][colNo] = 0;
    }

    if (colNo < colCount - 1)
        CalcRow(a, rowNo, colCount, colNo + 1, S, k);
}

void CalcRows(int** a, const int rowCount, const int colCount, int rowNo, int& S, int& k)
{
    CalcRow(a, rowNo, colCount, 0, S, k);
    if (rowNo < rowCount - 1)
        CalcRows(a, rowCount, colCount, rowNo + 1, S, k);
}