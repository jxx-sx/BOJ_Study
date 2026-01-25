#include <iostream>

using namespace std;

int arr[50][50];
bool visited[50][50];
int w, h;
int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
int dy[] = {0, 0, 1, -1, -1, -1, 1, 1};

bool valid(int x, int y) {
    if (x < 0 or h <= x)
        return false;
    if (y < 0 or w <= y)
        return false;
    return true;
}

void dfs(int x, int y) {
    visited[x][y] = true;
    for (int i = 0; i < 8; i++) {
        if (valid(x + dx[i], y + dy[i]))
            if (arr[x + dx[i]][y + dy[i]] and !visited[x + dx[i]][y + dy[i]])
                dfs(x + dx[i], y + dy[i]);
    }
}

bool init() {
    cin >> w >> h;
    if (w == 0 and h == 0)
        return false;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            cin >> arr[i][j];
            visited[i][j] = false;
        }

    return true;
}

void solve() {
    int cnt = 0;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (arr[i][j] and !visited[i][j]) {
                cnt++;
                dfs(i, j);
            }
    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}