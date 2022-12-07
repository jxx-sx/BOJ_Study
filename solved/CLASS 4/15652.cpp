#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> ans;
void dfs(int x, int l) {
    if (!ans.empty()) {
        if (ans.back() > x)
            return;
    }
    ans.push_back(x);
    if (l == m) {
        for (int i = 0; i < m; i++) {
            cout << ans[i] << ' ';
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
void init() { cin >> n >> m; }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    for (int i = 0; i < n; i++) {
        dfs(i + 1, 1);
    }
}