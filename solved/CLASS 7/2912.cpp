#include <algorithm>
#include <iostream>
#define sq 100

using namespace std;

struct Query {
    int s, e, i;
    bool operator<(const Query &t) const {
        if (s / sq < t.s / sq)
            return e < t.e;
        return s < t.s;
    }
} q[10000];

int n, m, c;
int l = 1, r;
int arr[300001];
int cnt[10001];
int ans[10000];

void init() {
    cin >> n >> c;
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
        while (r < q[i].e) {
            r++;
            cnt[arr[r]]++;
        }
        while (q[i].e < r) {
            cnt[arr[r]]--;
            r--;
        }
        while (l < q[i].s) {
            cnt[arr[l]]--;
            l++;
        }
        while (q[i].s < l) {
            l--;
            cnt[arr[l]]++;
        }
        for (int j = 1; j <= c; j++)
            if (cnt[j] > (r - l + 1) / 2)
                ans[q[i].i] = j;
    }
    for (int i = 0; i < m; i++) {
        if (ans[i])
            cout << "yes " << ans[i] << '\n';
        else
            cout << "no\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}