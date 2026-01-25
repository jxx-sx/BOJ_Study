#include <iostream>
#include <queue>
#include <vector>

#define N 10001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, arr[N], in[N];
vector<int> e[N];

void init() {
    int k, p;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i] >> k;
        while (k--) {
            cin >> p;
            e[p].pb(i);
            in[i]++;
        }
    }
}

void solve() {
    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= n; i++) {
        if (in[i])
            continue;
        pq.push({-arr[i], i});
    }
    int ans;
    while (!pq.empty()) {
        auto [dist, cur] = pq.top();
        pq.pop();
        ans = dist;
        for (auto a : e[cur]) {
            in[a]--;
            if (!in[a]) {
                pq.push({ans - arr[a], a});
            }
        }
    }
    cout << -ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}