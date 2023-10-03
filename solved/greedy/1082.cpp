#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int arr[10];
int ans[100];
vector<pair<int, int>> v;
int n, m;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        v.push_back({arr[i], i});
    }
    cin >> m;
    sort(v.begin(), v.end());
}

void solve() {
    if (v.front().second == 0 and v[1].first <= m) {
        ans[0] = v[1].second;
        m -= v[1].first;
    } else {
        ans[0] = v[0].second;
        m -= v[0].first;
    }
    if (!ans[0]) {
        cout << 0;
        return;
    }
    int cur = 1;
    while (m >= v[0].first) {
        ans[cur] = v[0].second;
        m -= v[0].first;
        cur++;
    }
    ans[cur] = -1;

    cur = 0;
    while (ans[cur] != -1) {
        for (int i = n - 1; i > ans[cur]; i--)
            if (arr[i] - arr[ans[cur]] <= m) {
                m -= arr[i] - arr[ans[cur]];
                ans[cur] = i;
                break;
            }
        cur++;
    }
    cur = 0;
    while (ans[cur] != -1) {
        cout << ans[cur];
        cur++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}