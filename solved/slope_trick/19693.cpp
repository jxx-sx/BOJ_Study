#include <iostream>
#include <queue>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;
ll ans, n, h;
priority_queue<ll> l, r;

void init() { cin >> n >> h; }

void solve() {
    ll x;
    cin >> x;
    l.push(x);
    r.push(-x);
    for (ll i = 1; i < n; i++) {
        cin >> x;
        if (l.top() > x + h * i) {
            ll tmp = l.top();
            l.push(x + h * i);
            l.push(x + h * i);
            l.pop();
            r.push(-tmp + 2 * h * i);
            ans += tmp - (x + h * i);
        } else if (r.top() > -x + h * i) {
            ll tmp = r.top();
            r.push(-x + h * i);
            r.push(-x + h * i);
            r.pop();
            l.push(-tmp + 2 * h * i);
            ans += tmp - (-x + h * i);
        } else {
            l.push(x + h * i);
            r.push(-x + h * i);
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}