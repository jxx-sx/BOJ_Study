#include <iostream>
#include <queue>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;
priority_queue<ll> pq;
ll n, m, ans;

void init() {
    cin >> n >> m;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        pq.push(-x);
    }
}

void solve() {
    while (m--) {
        ll x = pq.top();
        pq.pop();
        ll y = pq.top();
        pq.pop();
        pq.push(x + y);
        pq.push(x + y);
    }
    while (pq.size()) {
        ans -= pq.top();
        pq.pop();
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}