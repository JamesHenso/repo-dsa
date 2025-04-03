#pragma once
using namespace std;

void selectionSort(int* a, int n) {
    int i, j, posMin;
    for (i = 0; i < n - 1; i++) {
        posMin = i;
        for (j = i + 1; j < n; j++)
            if (a[j] < a[posMin]) posMin = j;
        swap(a[posMin], a[i]);
    }
}
