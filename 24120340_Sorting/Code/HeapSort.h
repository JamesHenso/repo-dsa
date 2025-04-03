#pragma once
using namespace std;

void heapify(int* a, int i, int n) {
    int value = a[i];
    int parent = i, child = parent * 2 + 1;
    while (child < n) {
        if (child < n - 1 && a[child] < a[child + 1]) ++child;
        if (value >= a[child]) break;
        a[parent] = a[child];
        parent = child;
        child = parent * 2 + 1;
    }
    a[parent] = value;
}

void heapSort(int* a, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) heapify(a, i, n);
    for (int i = n - 1; i >= 0; --i) swap(a[0], a[i]), heapify(a, 0, i);
}