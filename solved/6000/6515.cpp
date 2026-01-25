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
} q[100000];

int arr[100000];
int arr_cnt[200001];
int cnt[100002];
int ans[100000];
int cur;
int n, m;
int l, r;

bool init() {
    cin >> n;
    if (n == 0)
        return false;
    cin >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] += 100000;
    }
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }
    sort(q, q + m);
    for (int i = 2; i <= n; i++)
        cnt[i] = 0;
    for (int i = 0; i < 200001; i++)
        arr_cnt[i] = 0;
    l = r = 0;
    cnt[0] = 200000;
    cnt[1] = 1;
    arr_cnt[arr[0]]++;
    cur = 1;
    return true;
}

void solve() {
    for (int i = 0; i < m; i++) {
        while (r < (q[i].e - 1)) {
            r++;
            cnt[arr_cnt[arr[r]]]--;
            arr_cnt[arr[r]]++;
            cnt[arr_cnt[arr[r]]]++;
            if (cnt[cur + 1])
                cur++;
        }
        while ((q[i].e - 1) < r) {
            cnt[arr_cnt[arr[r]]]--;
            arr_cnt[arr[r]]--;
            cnt[arr_cnt[arr[r]]]++;
            if (cnt[cur] == 0)
                cur--;
            r--;
        }
        while (l < (q[i].s - 1)) {
            cnt[arr_cnt[arr[l]]]--;
            arr_cnt[arr[l]]--;
            cnt[arr_cnt[arr[l]]]++;
            if (cnt[cur] == 0)
                cur--;
            l++;
        }
        while ((q[i].s - 1) < l) {
            l--;
            cnt[arr_cnt[arr[l]]]--;
            arr_cnt[arr[l]]++;
            cnt[arr_cnt[arr[l]]]++;
            if (cnt[cur + 1])
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

    while (init())
        solve();

    return 0;
}