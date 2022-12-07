#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int arr[3], tmp[3];
    arr[0] = arr[1] = arr[2] = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tmp[0] >> tmp[1] >> tmp[2];
        tmp[0] += ((arr[1] < arr[2]) ? arr[1] : arr[2]);
        tmp[1] += ((arr[0] < arr[2]) ? arr[0] : arr[2]);
        tmp[2] += ((arr[1] < arr[0]) ? arr[1] : arr[0]);
        arr[0] = tmp[0];
        arr[1] = tmp[1];
        arr[2] = tmp[2];
    }
    cout << min(arr[0], min(arr[1], arr[2]));
}
