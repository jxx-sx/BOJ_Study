#include <algorithm>
#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    int arr2[arr[n - 1] + 1];
    arr2[0] = arr2[1] = 0;
    for (int i = 2; i <= arr[n - 1]; i++) {
        arr2[i] = 1;
    }

    for (int i = 2; i <= arr[n - 1]; i++) {
        if (arr2[i] == 1) {
            for (int j = 2; j <= arr[n - 1] / i; j++) {
                arr2[i * j] = 0;
            }
        } else
            continue;
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += arr2[arr[i]];
    }
    cout << count << endl;
}