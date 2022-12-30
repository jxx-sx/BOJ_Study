#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int n, m;
vector<bool> check = vector<bool>(8, false);
vector<int> datas, ans;
vector<int> isUsed[8];

void dfs(int x, int l) {
    if (check[x])
        return;

    if (!isUsed[l].empty())
        if (isUsed[l].back() == datas[x])
            return;

    check[x] = true;
    ans.push_back(x);
    isUsed[l].push_back(datas[x]);
    l += 1;

    if (l == m) {
        for (auto i : ans)
            cout << datas[i] << ' ';
        cout << '\n';
    } else {
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
        datas.push_back(num);
    }
    sort(datas.begin(), datas.end());
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