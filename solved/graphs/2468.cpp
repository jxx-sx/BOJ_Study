#include <iostream>

#define OPTIMIZE

#ifdef OPTIMIZE
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif

using namespace std;

int n, cur;
int arr[100][100];
int visited[100][100];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or n <= y)
        return false;
    return true;
}

void dfs(int x, int y) {
    if (visited[x][y] == cur)
        return;
    if (arr[x][y] <= cur)
        return;
    visited[x][y] = cur;
    for (int i = 0; i < 4; i++) {
        if (!valid(x + dx[i], y + dy[i]))
            continue;
        dfs(x + dx[i], y + dy[i]);
    }
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
}

void solve() {
    int ans = 1;
    while (++cur <= 100) {
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (arr[i][j] > cur and visited[i][j] < cur) {
                    cnt++;
                    dfs(i, j);
                }
        ans = max(cnt, ans);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}