#include <iostream>

using namespace std;

char arr[600][600];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int n, m, sx, sy, ans;

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or m <= y)
        return false;
    return true;
}

void dfs(int x, int y) {
    if (arr[x][y] == 'P')
        ans++;
    arr[x][y] = 'X';
    for (int i = 0; i < 4; i++) {
        if (valid(x + dx[i], y + dy[i]))
            if (arr[x + dx[i]][y + dy[i]] != 'X')
                dfs(x + dx[i], y + dy[i]);
    }
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 'I') {
                sx = i;
                sy = j;
            }
        }
}

void solve() {
    dfs(sx, sy);
    if (ans)
        cout << ans;
    else
        cout << "TT";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}