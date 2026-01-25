#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, tmp, arr[4] = {0};
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        if (i == 0) {
            arr[0] = 0;
            arr[1] = tmp;
            arr[2] = tmp;
        } else {
            arr[3] = max(arr[1], arr[2]);
            arr[2] = arr[1] + tmp;
            arr[1] = arr[0] + tmp;
            arr[0] = arr[3];
        }
    }
    cout << max(arr[1], arr[2]);
}