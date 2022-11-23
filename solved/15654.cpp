#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
bool check[8];
vector<int> ans;
vector<int> datas;
void dfs(int x, int l) {
    if (check[x])
        return;
    check[x] = true;
    ans.push_back(x);
    if (l == m) {
        for (int i = 0; i < m; i++) {
            cout << datas[ans[i]] << ' ';
        }
        cout << '\n';
    } else {
        for (int i = 0; i < n; i++) {
            dfs(i, l + 1);
        }
    }
    check[x] = false;
    ans.pop_back();
    return;
}
void init() {
    for (int i = 0; i < 8; i++) {
        check[i] = false;
    }
    cin >> n >> m;
    int tmp;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        datas.push_back(tmp);
    }
    sort(datas.begin(), datas.end());
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    for (int i = 0; i < n; i++) {
        dfs(i, 1);
    }
}