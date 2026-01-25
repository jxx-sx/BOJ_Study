#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int n, m;
vector<int> ans, num;

void dfs(int x, int l) {
    if (!ans.empty()) {
        if (ans.back() > x)
            return;
    }
    ans.push_back(x);
    if (l == m) {
        for (auto i : ans) {
            cout << num[i - 1] << ' ';
        }
        cout << '\n';
    } else {
        for (int i = 0; i < n; i++) {
            dfs(i + 1, l + 1);
        }
    }
    ans.pop_back();
    return;
}
void init() {
    int inp;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> inp;
        num.push_back(inp);
    }
    sort(num.begin(), num.end());
}

void solve() {
    for (int i = 0; i < n; i++) {
        dfs(i + 1, 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}