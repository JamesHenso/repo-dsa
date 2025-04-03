#include <iostream>

using namespace std;

int searchMinRotate(int a[], int n)
{
    if (a[0] < a[n - 1])
    {
        return a[0];
    }
    int left = 0, right = n - 1;
    while (left < right)
    {
        if (a[left] <= a[right])
        {
            return a[left];
        }
        int mid = left + (right - left) / 2;
        if (a[left] > a[mid])
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return a[left];
}

int main()
{
    int n, key;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int result = searchMinRotate(arr, n);
    cout << result << endl;

    return 0;
}