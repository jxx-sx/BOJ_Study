#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

long long arr[2001][2001];
int n, m, q;

void init() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
            arr[i][j] += arr[i - 1][j - 1] + arr[i - 1][j];
            if (i > 2)
                arr[i][j] -= arr[i - 2][j - 1];
        }
}

void solve() {
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << arr[x][y] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}