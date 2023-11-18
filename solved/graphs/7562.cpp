#include <iostream>
#include <memory.h>
#include <queue>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
int n;
int visited[300][300];
pair<int, int> src, dst;

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or n <= y)
        return false;
    return true;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            visited[i][j] = 0;
    cin >> src.first >> src.second >> dst.first >> dst.second;
}

void solve() {
    queue<pair<int, int>> q;
    visited[src.first][src.second] = 1;
    q.push(src);
    while (q.size()) {
        if (q.front() == dst) {
            cout << visited[dst.first][dst.second] - 1 << '\n';
            return;
        }
        int x = q.front().first;
        int y = q.front().second;
        for (int i = 0; i < 8; i++) {
            if (valid(x + dx[i], y + dy[i]) and !visited[x + dx[i]][y + dy[i]]) {
                visited[x + dx[i]][y + dy[i]] = visited[x][y] + 1;
                q.push({x + dx[i], y + dy[i]});
            }
        }
        q.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}