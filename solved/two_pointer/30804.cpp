#include <iostream>

#define N 200000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, ans, l, r, arr[N], cur, cnt[10];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    while (r != n) {
        if (!cnt[arr[r]])
            cur++;
        cnt[arr[r]]++;
        r++;
        while (cur > 2) {
            cnt[arr[l]]--;
            if (!cnt[arr[l]])
                cur--;
            l++;
        }
        ans = max(ans, r - l);
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