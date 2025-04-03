#pragma once
using namespace std;

int maxBit(int* a, int n){
    int res = 0;
    for(int i = 0; i < n; ++i){
        int bit = 0;
        int tmp = a[i];
        while(tmp){
            ++bit;
            tmp /= 2;
        }
        if(bit > res) res = bit;
    }
    return res;
}

void radixSort(int* a, int L, int R, int bit){
    if(bit == - 1) return;
    if(L >= R) return;
    int i = L, j = R;
    while(true){
        while((a[i] >> bit & 1) == 0 && i <= j) i++;
        while((a[j] >> bit & 1) == 1 && i <= j) j--;
        if(i > j) break;
        swap(a[i], a[j]);
    }
    // mang hien tai la a[L...j,i,...R]
    // phan hoach 2 mang va goi de quy ham radixSort
    radixSort(a, L, j, bit - 1);
    radixSort(a, i, R, bit - 1);
}

void radixSort(int* a, int n){
    int bit = maxBit(a, n);
    radixSort(a, 0, n - 1, bit);
}