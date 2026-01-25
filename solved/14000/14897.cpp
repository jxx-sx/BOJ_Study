#include <algorithm>
#include <iostream>
#define sq 1000

using namespace std;

struct Query {
    int s, e, i;
    bool operator<(const Query &t) const {
        if (s / sq == t.s / sq)
            return e < t.e;
        return s < t.s;
    }
} q[1000000];

int arr[1000000];
int coord[1000000];
int cnt[1000000];
int ans[1000000];
int cur;
int n, m;
int l, r;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        coord[i] = arr[i];
    }
    sort(coord, coord + n);
    for (int i = 0; i < n; i++)
        arr[i] = lower_bound(coord, coord + n, arr[i]) - coord;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }
    sort(q, q + m);
    cnt[arr[l]]++;
    cur++;
}

void solve() {
    for (int i = 0; i < m; i++) {
        while (r < (q[i].e - 1)) {
            r++;
            if (cnt[arr[r]] == 0)
                cur++;
            cnt[arr[r]]++;
        }
        while ((q[i].e - 1) < r) {
            cnt[arr[r]]--;
            if (cnt[arr[r]] == 0)
                cur--;
            r--;
        }
        while (l < (q[i].s - 1)) {
            cnt[arr[l]]--;
            if (cnt[arr[l]] == 0)
                cur--;
            l++;
        }
        while ((q[i].s - 1) < l) {
            l--;
            if (cnt[arr[l]] == 0)
                cur++;
            cnt[arr[l]]++;
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