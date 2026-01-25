#include <algorithm>
#include <iostream>
#define sq 500

using namespace std;

struct Query {
    int s, e, i;
    bool operator<(const Query &t) const {
        if (s / sq == t.s / sq)
            return e < t.e;
        return s < t.s;
    }
} q[100000];
int n, m;
int cnt[100001];
int arr[100001];
int ans[100000];
int cur;
int l = 1, r;

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }
    sort(q, q + m);
}

void solve() {
    for (int i = 0; i < m; i++) {
        while (r < q[i].e) {
            r++;
            cnt[arr[r]]++;
            if (cnt[arr[r]] == 3)
                cur++;
        }
        while (q[i].e < r) {
            cnt[arr[r]]--;
            if (cnt[arr[r]] == 2)
                cur--;
            r--;
        }
        while (l < q[i].s) {
            cnt[arr[l]]--;
            if (cnt[arr[l]] == 2)
                cur--;
            l++;
        }
        while (q[i].s < l) {
            l--;
            cnt[arr[l]]++;
            if (cnt[arr[l]] == 3)
                cur++;
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