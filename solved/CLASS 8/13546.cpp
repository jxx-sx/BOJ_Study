#include <algorithm>
#include <deque>
#include <iostream>
#define Max 100001
#define sq 1000

using namespace std;

struct Query {
    int s, e, i;
} q[Max];

deque<int> dq[Max];
int n, m, k;
int ans[Max];
int arr[Max];
int cnt[Max];
int bucket[101];
int l, r;

bool comp(Query a, Query b) {
    if (a.s / sq == b.s / sq)
        return a.e < b.e;
    return a.s < b.s;
}
void update_l(int x) {
    while (l < x) { // minus
        cnt[dq[arr[l]].back() - dq[arr[l]].front()]--;
        bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]--;
        dq[arr[l]].pop_front();
        if (dq[arr[l]].size()) {
            cnt[dq[arr[l]].back() - dq[arr[l]].front()]++;
            bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]++;
        } else {
            cnt[0]++;
            bucket[0]++;
        }
        l++;
    }

    while (x < l) {
        l--;
        if (dq[arr[l]].size()) {
            cnt[dq[arr[l]].back() - dq[arr[l]].front()]--;
            bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]--;
        } else {
            cnt[0]--;
            bucket[0]--;
        }
        dq[arr[l]].push_front(l);
        cnt[dq[arr[l]].back() - dq[arr[l]].front()]++;
        bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]++;
    }
}

void update_r(int x) {
    while (r < x) {
        r++;
        if (dq[arr[r]].size()) {
            cnt[dq[arr[r]].back() - dq[arr[r]].front()]--;
            bucket[(dq[arr[r]].back() - dq[arr[r]].front()) / sq]--;
        } else {
            cnt[0]--;
            bucket[0]--;
        }
        dq[arr[r]].push_back(r);
        cnt[dq[arr[r]].back() - dq[arr[r]].front()]++;
        bucket[(dq[arr[r]].back() - dq[arr[r]].front()) / sq]++;
    }

    while (x < r) {
        cnt[dq[arr[r]].back() - dq[arr[r]].front()]--;
        bucket[(dq[arr[r]].back() - dq[arr[r]].front()) / sq]--;
        dq[arr[r]].pop_back();
        if (dq[arr[r]].size()) {
            cnt[dq[arr[r]].back() - dq[arr[r]].front()]++;
            bucket[(dq[arr[r]].back() - dq[arr[r]].front()) / sq]++;
        } else {
            cnt[0]++;
            bucket[0]++;
        }
        r--;
    }
}

int find_max_bucket(int x) {
    for (int i = min((x + 1) * sq - 1, n); i >= 0; i--)
        if (cnt[i])
            return i;
    return 0;
}

int find_max() {
    for (int i = 100; i >= 0; i--)
        if (bucket[i])
            return find_max_bucket(i);
    return 0;
}

void init() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
    }
    sort(q, q + m, comp);
    dq[arr[0]].push_back(0);
    cnt[0] = Max;
    bucket[0] = Max;
}

void solve() {
    for (int i = 0; i < m; i++) {
        update_r(q[i].e - 1);
        update_l(q[i].s - 1);
        ans[q[i].i] = find_max();
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