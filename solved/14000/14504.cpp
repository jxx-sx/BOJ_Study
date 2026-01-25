#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int n, m;
int arr[100001];
int sort_arr[100001];
int sq;

int get_bucket(int x) { return x / sq; }

void update(int i, int k) {
    if (get_bucket(i) == get_bucket(n - 1)) {
        *lower_bound(sort_arr + sq * get_bucket(i), sort_arr + n, arr[i]) = k;
        sort(sort_arr + sq * get_bucket(i), sort_arr + n);
    } else {
        *lower_bound(sort_arr + sq * get_bucket(i), sort_arr + sq * (get_bucket(i) + 1), arr[i]) = k;
        sort(sort_arr + sq * get_bucket(i), sort_arr + sq * (get_bucket(i) + 1));
    }
    arr[i] = k;
}

int query(int l, int r, int k) {
    int rtn = 0;
    int ls = get_bucket(l);
    int rs = get_bucket(r);

    if (get_bucket(l) == get_bucket(r))
        for (int i = l; i <= r; i++)
            rtn += arr[i] > k ? 1 : 0;
    else {
        for (int i = l; i < sq * (ls + 1); i++)
            rtn += arr[i] > k ? 1 : 0;
        for (int i = ls + 1; i < rs; i++)
            rtn += (sort_arr + sq * (i + 1)) - upper_bound(sort_arr + sq * i, sort_arr + sq * (i + 1), k);
        for (int i = sq * rs; i <= r; i++)
            rtn += arr[i] > k ? 1 : 0;
    }
    return rtn;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sort_arr[i] = arr[i];
    }
    cin >> m;

    sq = sqrt(n);
    for (int i = 0; i < (n - 1) / sq; i++)
        sort(sort_arr + sq * i, sort_arr + sq * (i + 1));
    sort(sort_arr + sq * ((n - 1) / sq), sort_arr + n);
}

void solve() {
    int q, a, b, c;
    while (m--) {
        cin >> q >> a >> b;
        if (q == 1) {
            cin >> c;
            cout << query(a - 1, b - 1, c) << '\n';
        } else
            update(a - 1, b);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}