#pragma once

void flashSort(int* a, int n) {
    int m = 0.43 * n;
    int* L = new int[m]{};
    int minA = a[0], maxA = a[0];
    for (int i = 1; i < n; ++i) {
        if (minA > a[i]) minA = a[i];
        if (maxA < a[i]) maxA = a[i];
    }
    // parse 1: classification
    for (int i = 0; i < n; ++i) {
        int k = 1ll * (m - 1) * (a[i] - minA) / (maxA - minA);
        ++L[k];
    }
    for (int i = 1; i < m; ++i)
        L[i] += L[i - 1];
    // parse 2: permutation cycle
    int cnt = 0, i = 0, k = m - 1;
    while (cnt < n) {
        while (i > L[k] - 1) {
            ++i;
            k = 1ll * (m - 1) * (a[i] - minA) / (maxA - minA);
        }
        int x = a[i]; //bat dau chu trinh
        while (i < L[k]) {
            k = 1ll * (m - 1) * (x - minA) / (maxA - minA); 
            int y = a[L[k] - 1];
            a[L[k] - 1] = x;
            x = y;
            --L[k];
            ++cnt;
        }
    }
    //parse 3: sorting each block with insertion sort   
    for (int j = 0; ++j < n;) {
        int value = a[j];
        i = j;
        while ((--i >= 0) && ((k = a[i]) > value))
            a[i + 1] = k;
        a[i + 1] = value;
    }
    delete[] L;
}