#include <iostream>
#include <queue>

using namespace std;

int n, m;
priority_queue<int, vector<int>, greater<int>> pq;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    vector<int> v[n];
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    int s, e;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        arr[e - 1]++;
        v[s - 1].push_back(e - 1);
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0)
            pq.push(i);
    }

    while (!pq.empty()) {
        int cur = pq.top();
        pq.pop();
        for (int i = 0; i < v[cur].size(); i++) {
            if (--arr[v[cur][i]] == 0) {
                pq.push(v[cur][i]);
            }
        }
        cout << cur + 1 << ' ';
    }
}