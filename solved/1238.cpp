#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, x;
    cin >> n >> m >> x;
    int arr[n + 1][n + 1];
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            arr[i][j] = 10000000;
        }
        arr[i][i] = 0;
    }

    int s, e, t;
    for (int i = 0; i < m; i++) {
        cin >> s >> e >> t;
        arr[s][e] = t;
    }

    for (int k = 1; k < n + 1; k++) {
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < n + 1; j++) {
                arr[i][j] = (arr[i][j] < arr[i][k] + arr[k][j] ? arr[i][j] : arr[i][k] + arr[k][j]);
            }
        }
    }
    
    int ans = 0;
    for (int i = 1; i < n + 1; i++) {
        ans = (ans > arr[i][x] + arr[x][i] ? ans : arr[i][x] + arr[x][i]);
    }
    cout << ans;
}