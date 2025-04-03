#include <iostream>
#include <vector>

using namespace std;

int minimumLength(vector<int> nums, int target) {
    int n = nums.size();
    int min_length = INT_MAX;
    int start = 0, end = 0, sum = 0;

    while (end < n) {
        sum += nums[end++];

        while (sum >= target) {
            min_length = min(min_length, end - start);
            sum -= nums[start++];
        }
    }

    return (min_length == INT_MAX) ? 0 : min_length;
}

int main() {
    int n, target;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    cin >> target;

    int result = minimumLength(nums, target);

    cout << result;

    return result;
}
