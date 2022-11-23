#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int arr[1025][1025];
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < 1025; i++) {
        arr[i][0] = 0;
        arr[0][i] = 0;
    }
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cin >> arr[i][j];
            arr[i][j] += arr[i][j - 1];
        }
    }
    int a, b, c, d, sum;
    for (int i = 0; i < m; i++) {
        sum = 0;
        cin >> a >> b >> c >> d;
        for (int j = a; j <= c; j++) {
            sum += arr[j][d] - arr[j][b - 1];
        }
        cout << sum << '\n';
    }
}