#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m;
int arr[32000];
vector<int> v[32000];

void solve() {
    priority_queue<int> pq;
    for (int i = 0; i < n; i++)
        if (arr[i] == 0)
            pq.push(-i);

    while (!pq.empty()) {
        int cur = -pq.top();
        pq.pop();
        for (int i = 0; i < v[cur].size(); i++) {
            if (--arr[v[cur][i]] == 0) {
                pq.push(-v[cur][i]);
            }
        }
        cout << cur + 1 << ' ';
    }
    return;
}

void init() {
    int s, e;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        arr[i] = 0;

    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        arr[e - 1]++;
        v[s - 1].push_back(e - 1);
    }
    solve();

    return;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();

    return 0;
}