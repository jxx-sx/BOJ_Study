#include <iostream>
#include <queue>

using namespace std;

int arr[64][64];
bool visited[64][64];
int n;
queue<pair<int, int>> q;

bool valid(int x, int y) {
    if (n <= x or n <= y)
        return false;
    if (visited[x][y])
        return false;
    return true;
}

bool bfs() {
    int x, y;
    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        if (valid(x, y + arr[x][y])) {
            if (x == n - 1 and y + arr[x][y] == n - 1)
                return true;
            q.push({x, y + arr[x][y]});
            visited[x][y + arr[x][y]] = true;
        }
        if (valid(x + arr[x][y], y)) {
            if (x + arr[x][y] == n - 1 and y == n - 1)
                return true;
            q.push({x + arr[x][y], y});
            visited[x + arr[x][y]][y] = true;
        }
    }
    return false;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
    visited[0][0] = true;
    q.push({0, 0});
}

void solve() {
    if (bfs())
        cout << "HaruHaru";
    else
        cout << "Hing";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}