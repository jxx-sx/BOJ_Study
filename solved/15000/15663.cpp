#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int n, m;
vector<bool> check = vector<bool>(8, false);
vector<int> data_set, ans;
vector<int> isUsed[8];

void dfs(int x, int l) {
    if (check[x])
        return;

    if (!isUsed[l].empty())
        if (isUsed[l].back() == data_set[x])
            return;

    check[x] = true;
    ans.push_back(x);
    isUsed[l].push_back(data_set[x]);
    l += 1;

    if (l == m) {
        for (auto i : ans)
            cout << data_set[i] << ' ';
        cout << '\n';
    } else {
        isUsed[l].clear();
        for (int i = 0; i < n; i++) {
            dfs(i, l);
        }
    }

    check[x] = false;
    ans.pop_back();

    return;
}

void init() {
    cin >> n >> m;
    int num;
    for (int i = 0; i < n; i++) {
        cin >> num;
        data_set.push_back(num);
    }
    sort(data_set.begin(), data_set.end());
}

void solve() {
    for (int i = 0; i < n; i++)
        dfs(i, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}