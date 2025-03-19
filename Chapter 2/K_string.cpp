#include <iostream>

using namespace std;

void generateArr(int (*A)[5], int rol, int col){
    for(int i = 0; i < rol; i++ ){
        for(int j = 0; j < col; j++){
            A[i][j] = rand() % 2; 
        }
    }
}

void showMatrix(int (*A)[5], int rol, int col) {
    for(int i = 0; i < rol; i++) {
        for(int j = 0; j < col; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

int getval(int (*A)[5], int i, int j, int L, int H){
    if(i < 0 || i >= L || j < 0 || j >= H){
        return 0;
    }

    return A[i][j];
}

void findBlockMax(int (*A)[5], int r, int c, int L, int H,
                int size, bool **cntar, int &max_size)
{
    if(r >= L || c >= H ){
        return;
    }

    cntar[r][c] = true;
    size++;
    
    if(size > max_size){
        max_size = size;
    }

    int direction[][2] = {{-1,0}, {-1,-1}, {0,-1}, {1,-1},
                          {1,0}, {1,1}, {0,1}, {-1,1}};

    for(int i = 0; i < 8; i++){
        int new_i = r + direction[i][0];
        int new_j = c + direction[i][1];

        int val = getval(A, new_i, new_j, L, H);
        if(val > 0 && !cntar[new_i][new_j]){
            findBlockMax(A, new_i, new_j, L, H, size, cntar, max_size);
        }
    }

    cntar[r][c] = false;
}

int getMaxOnes(int(*A)[5], int rmax, int colmax){
    int max_size = 0;
    int size = 0;

    // Allocate memory for cntar
    bool **cntar = new bool*[rmax];
    for(int i = 0; i < rmax; i++){
        cntar[i] = new bool[colmax];
        fill(cntar[i], cntar[i] + colmax, false);
    }

    for(int i = 0; i < rmax; i++){
        for(int j = 0; j < colmax; j++){
            findBlockMax(A, i, j, rmax, colmax, size, cntar, max_size);
        }
    }

    // Deallocate memory for cntar
    for(int i = 0; i < rmax; i++){
        delete[] cntar[i];
    }
    delete[] cntar;

    return max_size;
}

int main()
{
    int A[5][5];

    generateArr(A, 5, 5);

    cout << "Generated Matrix:" << endl;
    showMatrix(A, 5, 5);

    int max = getMaxOnes(A, 5, 5);

    cout << "Maximum size of connected 1s: " << max << endl;

    return 0;
}

