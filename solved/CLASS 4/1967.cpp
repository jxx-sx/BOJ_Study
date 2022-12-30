#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
vector<pair<int, int>> edges[10001];
vector<bool> isVisit = vector<bool>(10001, false);
int n, ans = 0;

int dfs(int node) {
    vector<int> child;
    child.push_back(0);
    isVisit[node] = true;
    for (auto a : edges[node]) {
        if (!isVisit[a.second]) {
            child.push_back(a.first + dfs(a.second));
        }
    }
    if (child.size() > 2) {
        sort(child.begin(), child.end());
        ans = max(ans, child.back() + child[child.size() - 2]);
    } else {
        ans = max(ans, child.back());
    }
    return child.back();
}

void init() {
    int s, e, t;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e >> t;
        edges[s].push_back({t, e});
    }
    return;
}

void solve() {
    dfs(1);
    cout << ans;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}