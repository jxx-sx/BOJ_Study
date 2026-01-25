#include <algorithm>
#include <iostream>
#define M 100000
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
} q[M];

int arr[1000001];
long long cnt[1 << 21];
int n, m, k;
long long cur;
long long ans[M];
int l, r;

void init() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] ^= arr[i - 1];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }
    sort(q, q + m);
}

void solve() {
    l = r = q[0].s;
    cnt[arr[l]] = 1;
    cur = (arr[l] ^ arr[l - 1]) == k ? 1 : 0;
    for (int i = 0; i < m; i++) {
        while (r < q[i].e) {
            r++;
            cur += cnt[k ^ arr[r]];
            cur += (arr[r] ^ arr[l - 1]) == k ? 1 : 0;
            cnt[arr[r]]++;
        }
        while (q[i].s < l) {
            l--;
            cnt[arr[l]]++;
            cur += cnt[k ^ arr[l - 1]];
        }
        while (q[i].e < r) {
            cnt[arr[r]]--;
            cur -= (arr[r] ^ arr[l - 1]) == k ? 1 : 0;
            cur -= cnt[k ^ arr[r]];
            r--;
        }
        while (l < q[i].s) {
            cur -= cnt[k ^ arr[l - 1]];
            cnt[arr[l]]--;
            l++;
        }

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