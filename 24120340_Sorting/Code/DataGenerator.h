#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;

const int RANGE = 300000;
const int FACTOR = ceil(1.0 * RANGE / RAND_MAX);

template <class T>
void HoanVi(T &a, T &b)
{
    T x = a;
    a = b;
    b = x;
}

int MyRand()
{
    // const int RANGE = 300000 -> FACTOR = 10
    // scale up random range from [0, RAND_MAX) to [0, RANGE)
    int r = FACTOR * rand();
    int add = rand() % FACTOR;
    return (r + add) % RANGE;
}

void GenerateRandomData(int *a, int n)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++)
    {
        a[i] = MyRand();
    }
}

void GenerateSortedData(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
}

void GenerateReverseData(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = n - 1 - i;
    }
}

void GenerateNearlySortedData(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int r1 = MyRand() % n;
        int r2 = MyRand() % n;
        HoanVi(a[r1], a[r2]);
    }
}

void generateData(int *a, int n, int t)
{
    switch (t)
    {
    case 0:
        GenerateRandomData(a, n);
        break;
    case 1:
        GenerateSortedData(a, n);
        break;
    case 2:
        GenerateReverseData(a, n);
        break;
    case 3:
        GenerateNearlySortedData(a, n);
        break;
    default:
        cout << "Error: unknown data type!\n";
    }
}

void print(int *arr, int n)
{
    cout << "> ";
    for (int i = 0; i < n; i++)
    {
        cout << setw(3) << arr[i];
    }
    cout << '\n';
}

void restoreArray(int *source, int *&a, int n)
{
    if (a != NULL)
    {
        delete[] a;
    }
    a = new int[n];
    for (int i = 0; i < n; ++i)
        a[i] = source[i];
}