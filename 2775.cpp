#include <iostream>

using namespace std;
int arr[15][14];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < 14; i++) {
        arr[0][i] = i + 1;
    }

    for (int i = 1; i < 15; i++) {
        arr[i][0] = arr[i - 1][0];
        for (int j = 1; j < 14; j++) {
            arr[i][j] = arr[i][j - 1] + arr[i - 1][j];
        }
    }
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        cout << arr[a][b - 1] << '\n';
    }
}