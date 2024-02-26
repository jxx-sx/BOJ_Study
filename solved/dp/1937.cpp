#include <iostream>
#include <queue>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int dp[500][500];
int arr[500][500];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n, ans;

struct Node {
    int x, y;
    Node(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const Node &t) const { return arr[x][y] > arr[t.x][t.y]; }
};

priority_queue<Node> pq;

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    return 0 <= y and y < n;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            pq.push(Node(i, j));
        }
}

void solve() {
    while (!pq.empty()) {
        int x = pq.top().x;
        int y = pq.top().y;
        pq.pop();
        for (int i = 0; i < 4; i++) {
            if (valid(x + dx[i], y + dy[i]) and arr[x + dx[i]][y + dy[i]] > arr[x][y]) {
                dp[x + dx[i]][y + dy[i]] = max(dp[x + dx[i]][y + dy[i]], dp[x][y] + 1);
                ans = max(dp[x + dx[i]][y + dy[i]], ans);
            }
        }
    }
    cout << ans + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}