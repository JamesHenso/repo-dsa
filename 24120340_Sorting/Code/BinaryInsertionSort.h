#pragma once
using namespace std;

int binarySearch(int* a, int value, int left, int right) {
    if (right <= left) return (value > a[left]) ? (left + 1) : left;
    int mid = (left + right) / 2;
    if (value > a[mid]) return binarySearch(a, value, mid + 1, right);
    return binarySearch(a, value, left, mid - 1);
}

void binaryInsertionSort(int* a, int n) {
    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        int selected = a[i];
        // find location where selected sould be inseretd
        int pos = binarySearch(a, selected, 0, j);
        // Move all elements after location to create space
        while (j >= pos) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
}