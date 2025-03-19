#include <iostream>

using namespace std;


int fibonacci(int n){
    if(n == 0) return 0; // f(0) = 0
    if(n == 1) return 1; // f(1) = 1

    return fibonacci(n-1) + fibonacci(n-2); // f(n) = f(n-1) + f(n-2)


}

int main(){
    int n; cin >> n; // Number to solve fibo

    return 0;
}