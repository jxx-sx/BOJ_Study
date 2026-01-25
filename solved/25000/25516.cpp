#include <iostream>
#include <queue>
#include <vector>

using namespace std;
vector<int> edges[100000];
queue<pair<int, int>> q;
bool visited[100000];
int arr[100000];
int n, k;
int ans;

void bfs() {
    while (!q.empty()) {
        if (arr[q.front().first])
            ans++;
        if (q.front().second < k)
            for (auto a : edges[q.front().first])
                if (!visited[a]) {
                    q.push({a, q.front().second + 1});
                    visited[a] = true;
                }
        q.pop();
    }
}

void init() {
    int s, e;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e;
        edges[s].push_back(e);
        edges[e].push_back(s);
    }
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    q.push({0, 0});
    visited[0] = true;
}

void solve() {
    bfs();
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}