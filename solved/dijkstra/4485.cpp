#include <iostream>
#include <memory.h>
#include <queue>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Node {
    int x, y, d;
    Node(int x = 0, int y = 0, int d = 0) : x(x), y(y), d(d) {}
    bool operator<(const Node &t) const { return d > t.d; }
};

int n, tc;
int arr[125][125];
bool visited[125][125];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or n <= y)
        return false;
    return !visited[x][y];
}

bool init() {
    memset(visited, 0, sizeof visited);
    cin >> n;
    if (!n)
        return false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
    tc++;
    return true;
}

void solve() {
    cout << "Problem " << tc << ": ";
    priority_queue<Node> pq;
    pq.push(Node(0, 0, arr[0][0]));
    visited[0][0] = true;
    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        if (cur.x == n - 1 and cur.y == n - 1) {
            cout << cur.d << '\n';
            return;
        }

        for (int i = 0; i < 4; i++) {
            int tmp_x = cur.x + dx[i];
            int tmp_y = cur.y + dy[i];
            if (valid(tmp_x, tmp_y)) {
                pq.push(Node(tmp_x, tmp_y, cur.d + arr[tmp_x][tmp_y]));
                visited[tmp_x][tmp_y] = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}