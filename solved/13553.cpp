#include <algorithm>
#include <iostream>
#define Max 100001
#define sq 500

using namespace std;

struct Query {
    int s, e, i;
    Query() {}
    Query(int s, int e, int i) : s(s), e(e), i(i) {}
    bool operator<(const Query &t) const {
        if (s / sq == t.s / sq)
            return e < t.e;
        return s < t.s;
    }
} q[Max];

long long ans[Max];
long long tree[Max];
long long cur;
int arr[Max];
int n, k, m;
int l = 1, r;

long long sum(int x) {
    long long rtn = 0;
    while (x) {
        rtn += tree[x];
        x -= (x & -x);
    }
    return rtn;
}

void update(int x, int d) {
    while (x < Max) {
        tree[x] += d;
        x += (x & -x);
    }
}

void update_l(int x) {
    while (l < x) {
        update(arr[l], -1);
        cur -= sum(min(arr[l] + k, 100000)) - sum(max(arr[l] - k - 1, 0));
        l++;
    }
    while (x < l) {
        l--;
        cur += sum(min(arr[l] + k, 100000)) - sum(max(arr[l] - k - 1, 0));
        update(arr[l], 1);
    }
}

void update_r(int x) {
    while (x < r) {
        update(arr[r], -1);
        cur -= sum(min(arr[r] + k, 100000)) - sum(max(arr[r] - k - 1, 0));
        r--;
    }
    while (r < x) {
        r++;
        cur += sum(min(arr[r] + k, 100000)) - sum(max(arr[r] - k - 1, 0));
        update(arr[r], 1);
    }
}

void init() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }
    sort(q, q + m);
}

void solve() {
    for (int i = 0; i < m; i++) {
        update_r(q[i].e);
        update_l(q[i].s);
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