#include <iostream>

using namespace std;

bool equalTarget(int n, int arr[], int target) {
    int start = 0, end = n - 1;

    while (start < end) {
        int sum = arr[start] + arr[end];
        if (sum > target) {
            end--;
        } else if (sum < target) {
            start++;
        } else {
            return true; 
        }
    }

    return false; 
}

int main() {
    int n, target;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> target;
    if (equalTarget(n, arr, target)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}