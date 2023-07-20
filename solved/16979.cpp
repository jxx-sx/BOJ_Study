#include <algorithm>
#include <iostream>
#define Max 100000
#define sq 1000

using namespace std;

struct Query {
    int s, e, i;
    Query() {}
    Query(int s, int e, int i) : s(s), e(e), i(i) {}
    bool operator<(const Query &t) const {
        if (s / sq != t.s / sq)
            return s < t.s;
        return e < t.e;
    }
} q[Max];

int n, m;
int tree[Max + 1];
int tmp[Max];
int arr[Max];
long long ans[Max];
long long cur;
int l, r;

int sum(int i) {
    int ans = 0;
    while (i) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}

void update(int i, int num) {
    while (i <= n) {
        tree[i] += num;
        i += (i & -i);
    }
}

void update_l(int x) {
    while (l < x) {
        cur -= sum(arr[l] - 1);
        update(arr[l], -1);
        l++;
    }
    while (x < l) {
        l--;
        cur += sum(arr[l] - 1);
        update(arr[l], 1);
    }
}

void update_r(int x) {
    while (r < x) {
        r++;
        cur += sum(n) - sum(arr[r]);
        update(arr[r], 1);
    }
    while (x < r) {
        cur -= sum(n) - sum(arr[r]);
        update(arr[r], -1);
        r--;
    }
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        tmp[i] = arr[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }

    sort(tmp, tmp + n);
    sort(q, q + m);

    for (int i = 0; i < n; i++)
        arr[i] = lower_bound(tmp, tmp + n, arr[i]) - tmp + 1;

    update(arr[0], 1);
}

void solve() {
    for (int i = 0; i < m; i++) {
        update_r(q[i].e - 1);
        update_l(q[i].s - 1);
        ans[q[i].i] = cur;
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