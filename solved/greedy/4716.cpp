#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long k, da, db;
    bool operator<(const Node &t) const { return abs(da - db) > abs(t.da - t.db); }
};

vector<Node> v;
long long n, a, b, ans;

bool init() {
    ans = 0;
    cin >> n >> a >> b;
    v.resize(n);

    for (auto &t : v)
        cin >> t.k >> t.da >> t.db;

    sort(v.begin(), v.end());
    return n != 0 or a != 0 or b != 0;
}

void solve() {
    for (auto t : v) {
        long long k;
        if (t.da < t.db) {
            k = min(t.k, a);
            ans += t.da * k;
            a -= k;
            t.k -= k;
            if (!t.k)
                continue;
            ans += t.db * t.k;
            b -= t.k;
        } else {
            k = min(t.k, b);
            ans += t.db * k;
            b -= k;
            t.k -= k;
            if (!t.k)
                continue;
            ans += t.da * t.k;
            a -= t.k;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}