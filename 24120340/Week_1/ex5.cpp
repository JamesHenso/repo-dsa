#include <iostream>

using namespace std;

bool check_sorted(int arr[], int i, int n){
    if(i == n-1){
        return true;
    }

    if(arr[i] > arr[i+1]){
        return false;
    }

    return check_sorted(arr, i+1, n);
}

int main(){
    int n;
    cout << "Input n: "; cin >> n;
    int arr[n];
    cout << "Input element: ";
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }
    if(check_sorted(arr, 0, n)){
        cout << "Sorted";
    } else {
        cout << "Unsorted";
    }

    return 0;
}