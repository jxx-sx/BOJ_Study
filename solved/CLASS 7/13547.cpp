#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
typedef pair<pair<int, int>, int> Q;

int n, m;
int arr[100001];
int ans[100000];
int cnt[1000001];
int cur;
Q query[100000];
int sqr;
int l = 1, r = 1;

bool compare(Q a, Q b) {
    if (a.first.first / sqr == b.first.first / sqr)
        return a.first.second < b.first.second;
    return a.first.first / sqr < b.first.first / sqr;
}

void updateL(int x) {
    while (l < x) {
        cnt[arr[l]]--;
        if (cnt[arr[l]] == 0)
            cur--;
        l++;
    }
    while (x < l) {
        l--;
        if (cnt[arr[l]] == 0)
            cur++;
        cnt[arr[l]]++;
    }
}

void updateR(int x) {
    while (r < x) {
        r++;
        if (cnt[arr[r]] == 0)
            cur++;
        cnt[arr[r]]++;
    }
    while (x < r) {
        cnt[arr[r]]--;
        if (cnt[arr[r]] == 0)
            cur--;
        r--;
    }
}

void init() {
    cin >> n;
    sqr = (int)sqrt(n);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> query[i].first.first >> query[i].first.second;
        query[i].second = i;
    }

    cnt[arr[1]] = 1;
    cur = 1;

    sort(query, query + m, compare);

    return;
}

void solve() {
    for (int i = 0; i < m; i++) {
        updateL(query[i].first.first);
        updateR(query[i].first.second);

        ans[query[i].second] = cur;
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