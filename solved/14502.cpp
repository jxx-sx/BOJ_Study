#include <iostream>
#include <vector>

using namespace std;

int ans = 0, n, m, dfs_count;
int arr[8][8], tmp[8][8];

vector<pair<int, int>> v;

void dfs(int x, int y) {
    tmp[x][y] = 2;

    if (x > 0)
        if (tmp[x - 1][y] == 0)
            dfs(x - 1, y);

    if (y > 0)
        if (tmp[x][y - 1] == 0)
            dfs(x, y - 1);

    if (x + 1 < n)
        if (tmp[x + 1][y] == 0)
            dfs(x + 1, y);

    if (y + 1 < m)
        if (tmp[x][y + 1] == 0)
            dfs(x, y + 1);
}

void dfs() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            tmp[i][j] = arr[i][j];

    for (int i = 0; i < v.size(); i++) {
        dfs(v[i].first, v[i].second);
    }

    dfs_count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tmp[i][j] == 0)
                dfs_count += 1;
        }
    }
    ans = max(ans, dfs_count);
}

void before_dfs() {
    for (int i = 0; i < n * m - 2; i++) {
        if (arr[i / m][i % m] == 0) {
            arr[i / m][i % m] = 1;
            for (int j = i + 1; j < n * m - 1; j++) {
                if (arr[j / m][j % m] == 0) {
                    arr[j / m][j % m] = 1;
                    for (int k = j + 1; k < n * m; k++) {
                        if (arr[k / m][k % m] == 0) {
                            arr[k / m][k % m] = 1;

                            dfs();

                            arr[k / m][k % m] = 0;
                        }
                    }
                    arr[j / m][j % m] = 0;
                }
            }
            arr[i / m][i % m] = 0;
        }
    }
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 2) {
                v.push_back({i, j});
            }
        }
    }
}

void solve() {
    init();
    before_dfs();
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}