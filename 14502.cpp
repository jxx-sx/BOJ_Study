#include <iostream>
#include <vector>

using namespace std;

int ans = 0, n, m, dfs_count;
int **arr, **tmp;
vector<pair<int, int>> v;

void dfs(int x, int y) {
    if (tmp[x][y] != 2)
        return;
    if (x > 0) {
        if (tmp[x - 1][y] == 0) {
            tmp[x - 1][y] = 2;
            dfs(x - 1, y);
        }
    }
    if (y > 0) {
        if (tmp[x][y - 1] == 0) {
            tmp[x][y - 1] = 2;
            dfs(x, y - 1);
        }
    }
    if (x + 1 < n) {
        if (tmp[x + 1][y] == 0) {
            tmp[x + 1][y] = 2;
            dfs(x + 1, y);
        }
    }
    if (y + 1 < n) {
        if (tmp[x][y + 1] == 0) {
            tmp[x][y + 1] = 2;
            dfs(x, y + 1);
        }
    }
}

void dfs() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tmp[i][j] != 3)
                tmp[i][j] = arr[i][j];
        }
    }

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
    for (int i = 0; i < n * m; i++) {
        if (arr[i / m][i % m] == 0) {
            tmp[i / m][i % m] = 3;
            for (int j = i + 1; j < n * m; j++) {
                if (arr[j / m][j % m] == 0) {
                    tmp[j / m][j % m] = 3;
                    for (int k = j + 1; k < n * m; k++) {
                        if (arr[k / m][k % m] == 0) {
                            tmp[k / m][k % m] = 3;
                            dfs();
                            tmp[k / m][k % m] = 0;
                        }
                    }
                    tmp[j / m][j % m] = 0;
                }
            }
            tmp[i / m][i % m] = 0;
        }
    }
}

void init() {
    cin >> n >> m;
    arr = new int *[n];
    tmp = new int *[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
        tmp[i] = new int[m];
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