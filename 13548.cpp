#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;
typedef pair<pair<int, int>, int> Q;

int n, m;
int arr[100001];
int cnt[100001];     // i의 갯수
int sum_cnt[100001]; // 각 갯수들의 배열
int ans[100000];
Q query[100000];
int cur_max; // cnt 최댓값
int sqr;
int l = 1, r = 1;

bool compare(Q a, Q b) {
    if (a.first.first / sqr == b.first.first / sqr)
        return a.first.second < b.first.second;
    return a.first.first < b.first.first;
}

void updateL(int x) {
    while (x < l) {
        l--;
        sum_cnt[cnt[arr[l]]]--;
        cnt[arr[l]]++;
        sum_cnt[cnt[arr[l]]]++;
        if (cnt[arr[l]] > cur_max)
            cur_max = cnt[arr[l]];
    }
    while (l < x) {
        if (cnt[arr[l]] == cur_max and sum_cnt[cnt[arr[l]]] == 1)
            cur_max--;
        sum_cnt[cnt[arr[l]]]--;
        cnt[arr[l]]--;
        sum_cnt[cnt[arr[l]]]++;
        l++;
    }
}

void updateR(int x) {
    while (x < r) {
        if (cnt[arr[r]] == cur_max and sum_cnt[cnt[arr[r]]] == 1)
            cur_max--;
        sum_cnt[cnt[arr[r]]]--;
        cnt[arr[r]]--;
        sum_cnt[cnt[arr[r]]]++;
        r--;
    }
    while (r < x) {
        r++;
        sum_cnt[cnt[arr[r]]]--;
        cnt[arr[r]]++;
        sum_cnt[cnt[arr[r]]]++;
        if (cnt[arr[r]] > cur_max)
            cur_max = cnt[arr[r]];
    }
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> query[i].first.first >> query[i].first.second;
        query[i].second = i;
    }

    sqr = (int)sqrt(n);
    cnt[1]++;
    cur_max = 1;

    sort(query, query + m, compare);
    return;
}

void solve() {
    for (int i = 0; i < m; i++) {
        updateL(query[i].first.first);
        updateR(query[i].first.second);

        ans[query[i].second] = cur_max;
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