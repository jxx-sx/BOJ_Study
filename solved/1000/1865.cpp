#include <iostream>

using namespace std;

int n, m, w, s, e, t;

void solve() {
    cin >> n >> m >> w;
    int *arr[n + 1];
    for (int j = 1; j < n + 1; j++) {
        arr[j] = new int[n + 1];
        for (int k = 1; k < n + 1; k++) {
            arr[j][k] = 1000001;
        }
        arr[j][j] = 0;
    }

    for (int j = 0; j < m; j++) {
        cin >> s >> e >> t;
        if (arr[s][e] > t)
            arr[e][s] = arr[s][e] = t;
    }
    for (int j = 0; j < w; j++) {
        cin >> s >> e >> t;
        if (arr[s][e] > -t) {
            arr[s][e] = -t;
        }
    }
    for (int j = 1; j < n + 1; j++) {
        for (int k = 1; k < n + 1; k++) {
            for (int l = 1; l < n + 1; l++) {
                if (arr[k][j] + arr[j][l] < arr[k][l]) {
                    arr[k][l] = arr[k][j] + arr[j][l];
                }
            }
        }
    }
    for (int i = 1; i < n + 1; i++)
        if (arr[i][i] < 0) {
            cout << "YES\n";
            return;
        }
    cout << "NO\n";
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    for (int i = 0; i < TC; i++) {
        solve();
    }
}
