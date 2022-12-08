#include <iostream>
#include <queue>

using namespace std;

int n;
priority_queue<pair<int, int>> pq;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int s, e;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s >> e;
        pq.push({-e, -s});
    }
    while (!pq.empty()) {
        cout << -pq.top().second << ' ' << -pq.top().first << '\n';
        pq.pop();
    }
}