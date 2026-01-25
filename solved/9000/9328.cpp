#include <iostream>
#include <memory.h>
#include <queue>
#include <string>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int h, w;
char arr[100][100];
bool visited[100][100];
bool key[26];
string keys;
int ans;

bool valid(int x, int y) {
    if (x < 0 or x >= h)
        return false;
    if (y < 0 or y >= w)
        return false;
    return arr[x][y] != '*' and !visited[x][y];
}

void init() {
    memset(visited, 0, sizeof visited);
    memset(key, 0, sizeof key);
    ans = 0;
    cin >> h >> w;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> arr[i][j];
    cin >> keys;
    if (keys[0] == '0')
        return;
    for (auto a : keys)
        key[a - 'a'] = true;
}

void solve() {
    queue<pair<int, int>> q;
    queue<pair<int, int>> door[26];
    for (int i = 0; i < w; i++) {
        if (arr[0][i] != '*') {
            q.push({0, i});
            visited[0][i] = true;
        }
        if (arr[h - 1][i] != '*') {
            q.push({h - 1, i});
            visited[h - 1][i] = true;
        }
    }

    for (int i = 1; i < h - 1; i++) {
        if (arr[i][0] != '*') {
            q.push({i, 0});
            visited[i][0] = true;
        }
        if (arr[i][w - 1] != '*') {
            q.push({i, w - 1});
            visited[i][w - 1] = true;
        }
    }

    while (!q.empty()) {
        char cur = arr[q.front().first][q.front().second];
        if ('A' <= cur and cur <= 'Z' and !key[cur - 'A']) {
            door[cur - 'A'].push({q.front().first, q.front().second});
            q.pop();
            continue;
        }
        if (cur == '$')
            ans++;
        if ('a' <= cur and cur <= 'z') {
            key[cur - 'a'] = true;
            while (!door[cur - 'a'].empty()) {
                q.push(door[cur - 'a'].front());
                door[cur - 'a'].pop();
            }
        }

        for (int i = 0; i < 4; i++) {
            int x = q.front().first + dx[i];
            int y = q.front().second + dy[i];
            if (valid(x, y)) {
                q.push({x, y});
                visited[x][y] = true;
            }
        }
        q.pop();
    }
    cout << ans << '\n';
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