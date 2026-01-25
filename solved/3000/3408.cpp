#include <algorithm>
#include <iostream>

#define N 200001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, prv[N], nxt[N], arr[N], _arr[N], cur[N];

bool dnc(int s = 1, int e = n) {
    if (e <= s)
        return true;
    int l = s;
    int r = e;
    while (l <= r) {
        if (prv[l] < s && e < nxt[l])
            return dnc(s, l - 1) && dnc(l + 1, e);
        if (prv[r] < s && e < nxt[r])
            return dnc(s, r - 1) && dnc(r + 1, e);
        l++, r--;
    }
    return false;
}

void init() {
    cin >> n;
    fill(cur, cur + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        _arr[i - 1] = arr[i];
    }
    sort(_arr, _arr + n);
    for (int i = 1; i <= n; i++) {
        int _i = lower_bound(_arr, _arr + n, arr[i]) - _arr;
        nxt[cur[_i]] = i;
        prv[i] = cur[_i];
        nxt[i] = N;
        cur[_i] = i;
    }
}

void solve() { cout << (dnc() ? "non-boring\n" : "boring\n"); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}