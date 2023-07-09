#include <iostream>
#include <queue>

using namespace std;
int arr[10001];
bool visited[10001];
int n;
int a, b;
queue<pair<int, int>> q;

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    cin >> a >> b;
    q.push({a, 0});
    visited[0] = visited[a] = true;
}

void solve() {
    while (!q.empty()) {
        if (q.front().first == b) {
            cout << q.front().second;
            return;
        }
        for (int i = q.front().first % arr[q.front().first]; i <= n; i += arr[q.front().first])
            if (!visited[i]) {
                q.push({i, q.front().second + 1});
                visited[i] = true;
            }
        q.pop();
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}