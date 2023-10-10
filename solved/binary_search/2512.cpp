#include <algorithm>
#include <iostream>

using namespace std;

int n, m, mx, arr[10000], sum[10001];

bool query(int x) {
    int i = lower_bound(arr, arr + n, x) - arr;
    if (m < x * (n - i) + sum[i])
        return false;
    mx = max(mx, x);
    return true;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> m;
    sort(arr, arr + n);
    for (int i = 0; i < n; i++)
        sum[i + 1] += sum[i] + arr[i];
}

void solve() {
    int l = 0, r = arr[n - 1];
    while (l <= r) {
        int m = (l + r) / 2;
        if (query(m))
            l = m + 1;
        else
            r = m - 1;
    }
    cout << mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}