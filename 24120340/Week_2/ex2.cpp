#include <iostream>
using namespace std;

int sentinelLinearSearch(int arr[], int n, int key) {
    int last = arr[n - 1];
    arr[n - 1] = key;
    int i = 0;
    while (arr[i] != key) {
        i++;
    }
    arr[n - 1] = last;
    if (i < n - 1 || arr[n - 1] == key) {
        return i;
    }
    return -1;
}

int main() {
    int n, key;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> key;
    cout << sentinelLinearSearch(arr, n, key);
    return 0;
}