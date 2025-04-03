#pragma once
using namespace std;
#include <ctime>

void quickSort(int* a, int low, int high) {
    int i = low;
    int j = high;
    int pivot = a[(i + j) / 2];
    int tmp;

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        } 
    }
    if (j > low) quickSort(a, low, j);
    if (i < high) quickSort(a, i, high);
}

void quickSort(int* a, int n) { quickSort(a, 0, n - 1); }