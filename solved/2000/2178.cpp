#include <iostream>
#include <queue>

using namespace std;
int n, m;
bool arr[100][100];
bool isVisit[100][100];
queue<pair<pair<int, int>, int>> q;

void bfs() {
    int x, y, distance;
    while (!q.empty()) {
        x = q.front().first.first;
        y = q.front().first.second;
        distance = q.front().second;
        q.pop();

        if (x == n - 1 and y == m - 1) {
            cout << distance;
            break;
        }
        if (x > 0)
            if (!isVisit[x - 1][y] and arr[x - 1][y]) {
                q.push({{x - 1, y}, distance + 1});
                isVisit[x - 1][y] = true;
            }
        if (x < n - 1)
            if (!isVisit[x + 1][y] and arr[x + 1][y]) {
                q.push({{x + 1, y}, distance + 1});
                isVisit[x + 1][y] = true;
            }
        if (y > 0)
            if (!isVisit[x][y - 1] and arr[x][y - 1]) {
                q.push({{x, y - 1}, distance + 1});
                isVisit[x][y - 1] = true;
            }
        if (y < m - 1)
            if (!isVisit[x][y + 1] and arr[x][y + 1]) {
                q.push({{x, y + 1}, distance + 1});
                isVisit[x][y + 1] = true;
            }
    }

    return;
}

void init() {
    cin >> n >> m;
    char ch;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> ch;
            if (ch == '1')
                arr[i][j] = true;
        }
    q.push({{0, 0}, 1});
    isVisit[0][0] = true;

    return;
}

void solve() {
    bfs();
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}