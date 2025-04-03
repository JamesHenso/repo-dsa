#pragma once

void countingSort(int* a, int n) {
    int maxValue = a[0];
    for (int i = 1; i < n; i++) maxValue = max(maxValue, a[i]);

    int* count = new int[maxValue + 1]{};
    int* output = new int[n];

    for (int i = 0; i < maxValue + 1; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[a[i]]++;
    for (int i = 1; i < maxValue + 1; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }
    for (int i = 0; i < n; i++) a[i] = output[i];

    delete[] count;
    delete[] output;
}