#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        int arr[2][n], tmp[3][n];
        for (int j = 0; j < n; j++)
            cin >> arr[0][j];
        for (int j = 0; j < n; j++)
            cin >> arr[1][j];
        tmp[0][0] = arr[0][0];
        tmp[1][0] = arr[1][0];
        tmp[2][0] = 0;
        for (int j = 1; j < n; j++) {
            tmp[0][j] = max(tmp[1][j - 1], tmp[2][j - 1]) + arr[0][j];
            tmp[1][j] = max(tmp[0][j - 1], tmp[2][j - 1]) + arr[1][j];
            tmp[2][j] = max(tmp[0][j - 1], max(tmp[1][j - 1], tmp[2][j - 1]));
        }
        cout << max(tmp[0][n - 1], max(tmp[1][n - 1], tmp[2][n - 1])) << '\n';
    }
}