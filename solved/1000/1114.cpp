#include <algorithm>
#include <iostream>
#include <set>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, k, c;
set<int> s;

void init() {
    cin >> n >> k >> c;
    int x;
    s.insert(0);
    s.insert(n);
    for (int i = 0; i < k; i++) {
        cin >> x;
        s.insert(n - x);
    }
}

void solve() {
    int l = 1, r = n;
    int ans = n;
    int last_cut, cnt, prv = 0;
    for (auto a : s) {
        l = max(a - prv, l);
        prv = a;
    }
    while (l <= r) {
        int m = (l + r) / 2;

        last_cut = 0;
        prv = 0;
        cnt = 0;

        for (auto a : s) {
            if (a - last_cut > m) {
                cnt++;
                last_cut = prv;
            }
            prv = a;
        }

        if (cnt > c) {
            l = m + 1;
        } else {
            ans = m;
            r = m - 1;
        }
    }
    cout << ans << ' ';

    last_cut = 0;
    prv = 0;
    cnt = 0;

    for (auto a : s) {
        if (a - last_cut > ans) {
            cnt++;
            last_cut = prv;
        }
        prv = a;
    }
    if (cnt == c) {
        cout << n - last_cut;
    } else {
        auto it = s.end();
        --it;
        --it;

        cout << (n - *it);
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}