#pragma once
using namespace std;

void insertionSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int cur = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > cur) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = cur;
    }
}
