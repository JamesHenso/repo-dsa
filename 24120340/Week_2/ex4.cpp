#include <iostream>
#include <numeric>

using namespace std;

int leastWeight(int n, int weight[], int days) {
    int high = std::accumulate(weight, weight + n, 0);
    int low = weight[0];
    int res = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int currentSum = 0, requiredDays = 1;

        for (int i = 0; i < n; i++) {
            if (currentSum + weight[i] > mid) {
                requiredDays++;
                currentSum = weight[i];
            } else {
                currentSum += weight[i];
            }
        }

        if (requiredDays <= days) {
            res = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return res;
}

int main() {
    int n, days;
    cin >> n;

    int weight[n];
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cin >> days;

    int result = leastWeight(n, weight, days);
    cout << result << endl;

    return 0;
}
