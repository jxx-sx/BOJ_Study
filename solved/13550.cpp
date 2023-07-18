#include <algorithm>
#include <iostream>
#include <list>
#define MaxN 100001
#define sq 1000

using namespace std;

struct Query {
    int s, e, i;
};

list<int> dq[1000000];
int arr[MaxN];
int ans[100000];
vector<Query> q;
int cnt[MaxN];
int bucket[1001];
int n, m, k;
int l, r;
int cur_max;

bool comp(Query a, Query b) {
    if (a.s / sq == b.s / sq)
        return a.e < b.e;
    return a.s < b.s;
}

void update_l(int x) {
    while (l < x) {
        cnt[dq[arr[l]].back() - dq[arr[l]].front()]--;
        bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]--;
        dq[arr[l]].pop_front();
        if (dq[arr[l]].size()) {
            cnt[dq[arr[l]].back() - dq[arr[l]].front()]++;
            bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]++;
        }
        l++;
    }

    while (x < l) {
        l--;
        if (dq[arr[l]].size()) {
            cnt[dq[arr[l]].back() - dq[arr[l]].front()]--;
            bucket[(dq[arr[l]].back() - dq[arr[l]].front()) / sq]--;
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
    for (int i = 1000; i >= 0; i--)
        if (bucket[i])
            return find_max_bucket(i);
    return 0;
}

void init() {
    Query input_query;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] += arr[i - 1];
        arr[i] %= k;
        arr[i] += k;
        arr[i] %= k;
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> input_query.s >> input_query.e;
        input_query.i = i;
        input_query.s--;
        q.push_back(input_query);
    }

    sort(q.begin(), q.end(), comp);

    dq[0].push_back(0);
    cnt[0] = 1;
    bucket[0] = 1;
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