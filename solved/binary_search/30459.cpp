#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m, r;
vector<long long> v, b;

long long find(long long x) {
    long long l = 0;
    long long r = b.size();
    long long mx = 0;
    while (l <= r) {
        long long m = (l + r) >> 1;
        if (b[m] <= x) {
            mx = max(mx, b[m]);
            l = m + 1;
        } else
            r = m - 1;
    }
    return mx;
}

void init() {
    cin >> n >> m >> r;
    v.resize(n);

    for (auto &a : v)
        cin >> a;

    r *= 2;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            b.push_back(abs(v[i] - v[j]));
    b.push_back(0);
    sort(b.begin(), b.end());
}

void solve() {
    long long ans = -1;
    while (m--) {
        long long x;
        cin >> x;
        long long tmp = find(r / x);
        if (!tmp)
            continue;
        if (tmp * x <= r) {
            ans = max(ans, tmp * x);
        }
    }

    if (ans == -1) {
        cout << -1;
        return;
    }
    cout << ans / 2 << (ans & 1 ? ".5" : ".0");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}