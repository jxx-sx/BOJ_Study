#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[2][50][50];
int r, c, t, ans;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
vector<pair<int, int>> cleaner;

bool valid(int x, int y) {
    if (x < 0 or r <= x)
        return false;
    if (y < 0 or c <= y)
        return false;
    for (auto a : cleaner)
        if (a == make_pair(x, y))
            return false;
    return true;
}

void propagate(int x, int y) {
    if (arr[0][x][y] == -1)
        return;
    int tmp = arr[0][x][y] / 5;
    arr[1][x][y] += arr[0][x][y];
    for (int i = 0; i < 4; i++)
        if (valid(x + dx[i], y + dy[i])) {
            arr[1][x + dx[i]][y + dy[i]] += tmp;
            arr[1][x][y] -= tmp;
        }
}

void clean() {
    int x = cleaner[0].first;
    for (int i = 1; i <= x; i++)
        arr[0][i][0] = arr[1][i - 1][0];
    for (int i = 0; i < x; i++)
        arr[0][i][c - 1] = arr[1][i + 1][c - 1];
    for (int i = 0; i < c - 1; i++)
        arr[0][0][i] = arr[1][0][i + 1];
    for (int i = 1; i < c; i++)
        arr[0][x][i] = arr[1][x][i - 1];

    x = cleaner[1].first;
    for (int i = x; i < r - 1; i++)
        arr[0][i][0] = arr[1][i + 1][0];
    for (int i = x + 1; i < r; i++)
        arr[0][i][c - 1] = arr[1][i - 1][c - 1];
    for (int i = 1; i < c; i++)
        arr[0][x][i] = arr[1][x][i - 1];
    for (int i = 0; i < c - 1; i++)
        arr[0][r - 1][i] = arr[1][r - 1][i + 1];
}

void init() {
    cin >> r >> c >> t;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            cin >> arr[0][i][j];
            if (arr[0][i][j] == -1)
                cleaner.push_back({i, j});
        }
}

void solve() {
    while (t--) {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                arr[1][i][j] = 0;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                propagate(i, j);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                arr[0][i][j] = arr[1][i][j];
        clean();
        for (auto a : cleaner)
            arr[0][a.first][a.second] = -1;
    }
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            ans += arr[0][i][j];
    cout << ans + 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}