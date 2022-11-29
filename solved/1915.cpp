#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int arr[n][m];
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c;
            if (c == '0')
                arr[i][j] = 0;
            else
                arr[i][j] = 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (arr[0][i] == 1 or arr[i][0] == 1) {
            ans = 1;
            break;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (arr[i][j] == 1) {
                arr[i][j] += min(arr[i][j - 1], min(arr[i - 1][j - 1], arr[i - 1][j]));
                ans = max(ans, arr[i][j]);
            }
        }
    }
    cout << ans * ans;
}