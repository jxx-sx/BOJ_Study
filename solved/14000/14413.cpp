#include <algorithm>
#include <iostream>
#define sq 3000

using namespace std;

struct Query {
    int s, e, i;
    bool operator<(const Query &t) const {
        if (s / sq == t.s / sq)
            return e < t.e;
        return s < t.s;
    }
} q[500000];

int arr[500000];
int coord[500000];
int arr_cnt[500001];
int cnt[500001];
int ans[500000];
int n, m;
int l, r;

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        coord[i] = arr[i];
    }
    sort(coord, coord + n);
    for (int i = 0; i < n; i++)
        arr[i] = lower_bound(coord, coord + n, arr[i]) - coord;
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }
    sort(q, q + m);
    cnt[0] = 500000;
    cnt[1] = 1;
    arr_cnt[arr[0]]++;
}

void solve() {
    for (int i = 0; i < m; i++) {
        while (r < (q[i].e - 1)) {
            r++;
            cnt[arr_cnt[arr[r]]]--;
            arr_cnt[arr[r]]++;
            cnt[arr_cnt[arr[r]]]++;
        }
        while ((q[i].e - 1) < r) {
            cnt[arr_cnt[arr[r]]]--;
            arr_cnt[arr[r]]--;
            cnt[arr_cnt[arr[r]]]++;
            r--;
        }
        while (l < (q[i].s - 1)) {
            cnt[arr_cnt[arr[l]]]--;
            arr_cnt[arr[l]]--;
            cnt[arr_cnt[arr[l]]]++;
            l++;
        }
        while ((q[i].s - 1) < l) {
            l--;
            cnt[arr_cnt[arr[l]]]--;
            arr_cnt[arr[l]]++;
            cnt[arr_cnt[arr[l]]]++;
        }
        ans[q[i].i] = cnt[2];
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