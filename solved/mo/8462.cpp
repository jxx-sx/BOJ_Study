#include <algorithm>
#include <iostream>
#define sq 100

using namespace std;

struct Query {
    int s, e, i;
    bool operator<(const Query &t) const {
        if (s / sq == t.s / sq)
            return e < t.e;
        return s < t.s;
    }
} q[100000];

int arr[100001];
int cnt[1000001];
int n, t;
int l = 1, r;
long long cur;
long long ans[100000];

void update(bool add, int i) {
    cur -= (long long)cnt[i] * cnt[i] * i;
    cnt[i] += add ? 1 : -1;
    cur += (long long)cnt[i] * cnt[i] * i;
}

void init() {
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 0; i < t; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }
    sort(q, q + t);
}

void solve() {
    for (int i = 0; i < t; i++) {
        while (r < q[i].e) {
            r++;
            update(true, arr[r]);
        }
        while (q[i].e < r) {
            update(false, arr[r]);
            r--;
        }
        while (l < q[i].s) {
            update(false, arr[l]);
            l++;
        }
        while (q[i].s < l) {
            l--;
            update(true, arr[l]);
        }

        ans[q[i].i] = cur;
    }

    for (int i = 0; i < t; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}