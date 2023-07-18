#include <algorithm>
#include <deque>
#include <iostream>
#define sq 1000

using namespace std;

deque<int> dq[200001];
int arr[100001];
int ans[100001];
int dist_cnt[100001];
int bucket[101];
int n, m;
int l, r;
int cur_max;

struct Query {
    int s, e, i;
} q[100001];

bool comp(Query a, Query b) {
    if (a.s / sq == b.s / sq)
        return a.e < b.e;
    return a.s < b.s;
}

void update_l(int x) {
    while (l < x) { // minus
        dist_cnt[dq[arr[l]].back() - dq[arr[l]].front()]--;
        bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]--;
        dq[arr[l]].pop_front();
        if (dq[arr[l]].size()) {
            dist_cnt[dq[arr[l]].back() - dq[arr[l]].front()]++;
            bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]++;
        } else {
            dist_cnt[0]++;
            bucket[0]++;
        }
        l++;
    }

    while (x < l) {
        l--;
        if (dq[arr[l]].size()) {
            dist_cnt[dq[arr[l]].back() - dq[arr[l]].front()]--;
            bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]--;
        } else {
            dist_cnt[0]--;
            bucket[0]--;
        }
        dq[arr[l]].push_front(l);
        dist_cnt[dq[arr[l]].back() - dq[arr[l]].front()]++;
        bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]++;
    }
}

void update_r(int x) {
    while (r < x) {
        r++;
        if (dq[arr[r]].size()) {
            dist_cnt[dq[arr[r]].back() - dq[arr[r]].front()]--;
            bucket[(dq[arr[r]].back() - dq[arr[r]].front()) / sq]--;
        } else {
            dist_cnt[0]--;
            bucket[0]--;
        }
        dq[arr[r]].push_back(r);
        dist_cnt[dq[arr[r]].back() - dq[arr[r]].front()]++;
        bucket[(dq[arr[r]].back() - dq[arr[r]].front()) / sq]++;
    }

    while (x < r) {
        dist_cnt[dq[arr[r]].back() - dq[arr[r]].front()]--;
        bucket[(dq[arr[r]].back() - dq[arr[r]].front()) / sq]--;
        dq[arr[r]].pop_back();
        if (dq[arr[r]].size()) {
            dist_cnt[dq[arr[r]].back() - dq[arr[r]].front()]++;
            bucket[(dq[arr[r]].back() - dq[arr[r]].front()) / sq]++;
        } else {
            dist_cnt[0]++;
            bucket[0]++;
        }
        r--;
    }
}

int find_max_bucket(int x) {
    for (int i = min((x + 1) * sq - 1, n); i >= 0; i--)
        if (dist_cnt[i])
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
    cin >> n;
    arr[0] = 100000;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] += arr[i - 1];
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].i = i;
        q[i].s--;
    }

    sort(q, q + m, comp);

    dq[100000].push_back(0);
    dist_cnt[0] = 100001;
    bucket[0] = 100001;
}

void solve() {
    for (int i = 0; i < m; i++) {
        update_r(q[i].e);
        update_l(q[i].s);
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