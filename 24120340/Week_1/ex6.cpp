#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int row, int col, int n, vector<vector<int>>& board) {
    // Check the column for any queens
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) return false;
    }

    // Check top-left to bottom-right diagonal
    for (int i = 1; i <= row; i++) {
        if (col - i >= 0 && board[row - i][col - i] == 1) return false;
    }

    // Check top-right to bottom-left diagonal
    for (int i = 1; i <= row; i++) {
        if (col + i < n && board[row - i][col + i] == 1) return false;
    }

    return true;
}

void N_queens(int n, int row, vector<vector<int>>& board, int& solutions) {
    if (row == n) {
        solutions++;
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, n, board)) {
            board[row][col] = 1;  // Place the queen
            N_queens(n, row + 1, board, solutions);  // Recur to place queen in the next row
            board[row][col] = 0;  // Backtrack
        }
    }
}

int main() {
    int n;
    cin >> n;  // Read the size of the board

    int solutions = 0;
    // Initialize the board with all cells as 0
    vector<vector<int>> solve(n, vector<int>(n, 0));

    // Start solving the N-Queens problem from the first row
    N_queens(n, 0, solve, solutions);

    cout << "Answer: " << solutions << endl;  // Output the number of solutions
    return 0;
}
