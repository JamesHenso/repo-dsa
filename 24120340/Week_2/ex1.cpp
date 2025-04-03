#include <iostream>
using namespace std;

// Function to perform linear search
int linearSearch(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return i; // Return the index of the target element
        }
    }
    return -1; // Return -1 if the target is not found
}

int main()
{
    int n, target;
    cin >> n;
    int arr[n];

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cin >> target;

    int result = linearSearch(arr, n, target);

    cout << result;

    return 0;
}