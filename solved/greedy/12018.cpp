#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> p[100], l;

void init() {
    int x;
    cin >> n >> m;
    l.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
        p[i].resize(l[i]);
        cin >> l[i];
        for (auto &a : p[i]) {
            cin >> a;
        }
        sort(p[i].begin(), p[i].end());
    }
}

void solve() {
    vector<int> ans;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!m)
            break;
        if (p[i].size() < l[i]) {
            cnt++;
            m--;
            continue;
        }
        ans.push_back(-p[i][p[i].size() - l[i]]);
    }
    sort(ans.begin(), ans.end());
    while (ans.size() and m > 0) {
        if (-ans.back() > m)
            break;
        cnt++;
        m += ans.back();
        ans.pop_back();
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}