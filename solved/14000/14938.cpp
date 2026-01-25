#include <iostream>
#define MAX 10000000
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, r, ans = 0;
    int s, e, t;
    cin >> n >> m >> r;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int dis[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dis[i][j] = MAX;
        }
        dis[i][i] = 0;
    }

    for (int i = 0; i < r; i++) {
        cin >> s >> e >> t;
        dis[s - 1][e - 1] = (t < dis[s - 1][e - 1] ? t : dis[s - 1][e - 1]);
        dis[e - 1][s - 1] = (t < dis[e - 1][s - 1] ? t : dis[e - 1][s - 1]);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dis[i][j] = (dis[i][j] < dis[i][k] + dis[k][j] ? dis[i][j] : dis[i][k] + dis[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int tmp = 0;
        for (int j = 0; j < n; j++) {
            if (dis[i][j] <= m) {
                tmp += arr[j];
            }
        }
        ans = (ans > tmp ? ans : tmp);
    }

    cout << ans << '\n';
}