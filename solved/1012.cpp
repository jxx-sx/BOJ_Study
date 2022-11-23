#include <iostream>
#include <vector>

using namespace std;

int t, m, n, k;
bool **arr;

void dfs(int a, int b) {
    if (arr[a][b]) {
        arr[a][b] = false;
        if (a != 0)
            dfs(a - 1, b);
        if (b != 0)
            dfs(a, b - 1);
        if (a != m - 1)
            dfs(a + 1, b);
        if (b != n - 1)
            dfs(a, b + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> m >> n >> k;
        arr = new bool *[m];
        for (int j = 0; j < m; j++) {
            arr[j] = new bool[n];
            for (int l = 0; l < n; l++) {
                arr[j][l] = false;
            }
        }

        vector<pair<int, int>> v;
        for (int j = 0; j < k; j++) {
            int x, y;
            cin >> x >> y;
            v.push_back({x, y});
            arr[x][y] = true;
        }
        int count = 0;
        for (int j = 0; j < v.size(); j++) {
            if (arr[v[j].first][v[j].second]) {
                dfs(v[j].first, v[j].second);
                count += 1;
            }
        }
        cout << count << '\n';
    }
}