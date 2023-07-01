#include <iostream>
#include <queue>

using namespace std;

int arr[1000][1000];
int ans[1000][1000];
int n, m;
pair<int, int> s;
queue<pair<int, int>> q;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            ans[i][j] = -1;
            if (arr[i][j] == 2)
                s = {i, j};
            if (arr[i][j] == 0)
                ans[i][j] = 0;
        }
}
bool val(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or m <= y)
        return false;
    return true;
}

void bfs() {
    q.push(s);
    ans[s.first][s.second] = 0;
    while (!q.empty()) {
        for (int i = 0; i < 4; i++)
            if (val(q.front().first + dx[i], q.front().second + dy[i])) {
                if (ans[q.front().first + dx[i]][q.front().second + dy[i]] == -1) {
                    ans[q.front().first + dx[i]][q.front().second + dy[i]] =
                        arr[q.front().first + dx[i]][q.front().second + dy[i]] == 0 ? 0 : ans[q.front().first][q.front().second] + 1;
                    if (ans[q.front().first + dx[i]][q.front().second + dy[i]] > 0)
                        q.push({q.front().first + dx[i], q.front().second + dy[i]});
                }
            }
        q.pop();
    }
}

void solve() {
    bfs();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << ans[i][j] << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}