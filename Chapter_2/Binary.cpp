#include <iostream>

using namespace std;

// make a function to random array A with different values

int *generateArray(int n){
    int *A = new int[n];
    for(int i = 0; i < n; i++){
        A[i] = rand() % 2;
    }
    return A;
}

void Binary(int n, int *A){
    if(n < 1){
        for(int i = 0; i < 5; i++) {
            printf("%d", A[i]);
        }
        printf("\n");
    }
    else{
        A[n-1] = 0;
        Binary(n - 1, A);
        A[n-1] = 1;
        Binary(n - 1, A);
    }
}
int main()
{
    int n = 5;

    int *A = generateArray(n);
    Binary(n, A);
    return 0;
}