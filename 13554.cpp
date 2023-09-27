#include <algorithm>
#include <iostream>
#define sq 500

using namespace std;

struct Query {
    int s, e, k, i;

    bool operator<(const Query &t) const {
        if (s / sq == t.s / sq)
            return e < t.e;
        return s < t.s;
    }
} q[100000];

long long arr_a[100001], arr_b[100001], ans[100000], cnt_a[100001], cnt_b[100001], cnt[100002];
int n, m, l = 1, r;

void update(int k, int i, long long d) {
    if (!d)
        return;

    long long *tree = k == 1 ? cnt_a : (k == 2 ? cnt_b : cnt);

    while (i <= 100000 + (k == 0 ? 1 : 0)) {
        tree[i] += d;
        i += (i & -i);
    }
}

long long sum(int k, int i) {
    long long *tree = k == 1 ? cnt_a : (k == 2 ? cnt_b : cnt);
    long long rtn = 0;

    while (i) {
        rtn += tree[i];
        i -= (i & -i);
    }
    return rtn;
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr_a[i];
    for (int i = 1; i <= n; i++)
        cin >> arr_b[i];
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e >> q[i].k;
        q[i].i = i;
    }
    sort(q, q + m);
}

void solve() {
    for (int i = 0; i < m; i++) {
        while (r < q[i].e) {
            r++;
            for (int i = 1; i <= 100000 / arr_a[r]; i++) {
                int tmp = sum(2, i) - sum(2, i - 1);
                update(0, i * arr_a[r] + 1, tmp);
            }
            for (int i = 1; i <= 100000 / arr_b[r]; i++) {
                int tmp = sum(1, i) - sum(1, i - 1);
                update(0, i * arr_b[r] + 1, tmp);
            }
            if (arr_a[r] * arr_b[r] <= 100000)
                update(0, arr_a[r] * arr_b[r] + 1, 1);
            update(1, arr_a[r], 1);
            update(2, arr_b[r], 1);
        }

        while (q[i].s < l) {
            l--;
            for (int i = 1; i <= 100000 / arr_a[l]; i++) {
                int tmp = sum(2, i) - sum(2, i - 1);
                update(0, i * arr_a[l] + 1, tmp);
            }
            for (int i = 1; i <= 100000 / arr_b[l]; i++) {
                int tmp = sum(1, i) - sum(1, i - 1);
                update(0, i * arr_b[l] + 1, tmp);
            }
            if (arr_a[l] * arr_b[l] <= 100000)
                update(0, arr_a[l] * arr_b[l] + 1, 1);
            update(1, arr_a[l], 1);
            update(2, arr_b[l], 1);
        }

        while (q[i].e < r) {
            update(1, arr_a[r], -1);
            update(2, arr_b[r], -1);
            for (int i = 1; i <= 100000 / arr_a[r]; i++) {
                int tmp = sum(2, i) - sum(2, i - 1);
                update(0, i * arr_a[r] + 1, -tmp);
            }
            for (int i = 1; i <= 100000 / arr_b[r]; i++) {
                int tmp = sum(1, i) - sum(1, i - 1);
                update(0, i * arr_b[r] + 1, -tmp);
            }
            if (arr_a[r] * arr_b[r] <= 100000)
                update(0, arr_a[r] * arr_b[r] + 1, -1);
            r--;
        }
        while (l < q[i].s) {
            update(1, arr_a[l], -1);
            update(2, arr_b[l], -1);
            for (int i = 1; i <= 100000 / arr_a[l]; i++) {
                int tmp = sum(2, i) - sum(2, i - 1);
                update(0, i * arr_a[l] + 1, -tmp);
            }
            for (int i = 1; i <= 100000 / arr_b[l]; i++) {
                int tmp = sum(1, i) - sum(1, i - 1);
                update(0, i * arr_b[l] + 1, -tmp);
            }
            if (arr_a[l] * arr_b[l] <= 100000)
                update(0, arr_a[l] * arr_b[l] + 1, -1);
            l++;
        }

        ans[q[i].i] = sum(0, q[i].k + 1);
    }
    for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}