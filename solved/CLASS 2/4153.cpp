#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int arr[3];
    while (true) {
        cin >> arr[0] >> arr[1] >> arr[2];
        sort(arr, arr + 3);
        if (arr[2] == 0)
            break;
        if (arr[0] * arr[0] + arr[1] * arr[1] == arr[2] * arr[2])
            cout << "right"
                 << "\n";
        else
            cout << "wrong"
                 << "\n";
    }
}