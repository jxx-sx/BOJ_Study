#include <iostream>
#include <queue>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

int n, a;
ll ans;
priority_queue<ll> pq;

void init() { cin >> n; }

void solve() {
    for (int i = 0; i < n; i++) {
        cin >> a;
        a -= i;
        if (!pq.empty() && a < pq.top()) {
            pq.push(a);
            ans += pq.top() - a;
            pq.pop();
        }
        pq.push(a);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}