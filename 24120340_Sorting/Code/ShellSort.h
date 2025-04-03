#pragma once
using namespace std;

void shellSort(int* a, int n) {
    int i, j, tmp;
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i += 1) {
            tmp = a[i];
            for (j = i; j >= gap && a[j - gap] > tmp; j -= gap)
                a[j] = a[j - gap];
            a[j] = tmp;
        }
}
