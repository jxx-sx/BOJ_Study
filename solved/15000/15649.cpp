#include <iostream>
#include <vector>

using namespace std;

int n, m;
bool check[9];
vector<int> ans;
void dfs(int x, int l) {
    if (check[x]) {
        return;
    }
    check[x] = true;
    ans.push_back(x);
    if (l == m) {
        for (int i = 0; i < m; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
    for (int i = 0; i < n; i++) {
        dfs(i + 1, l + 1);
    }
    check[x] = false;
    ans.pop_back();
    return;
}
void init() {
    for (int i = 0; i < 9; i++) {
        check[i] = false;
    }
    cin >> n >> m;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    for (int i = 0; i < n; i++) {
        dfs(i + 1, 1);
    }
}