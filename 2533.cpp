#include <iostream>
#include <vector>

using namespace std;
vector<int> child[1000001];
bool is_visit[1000001];
int ans, n;

pair<int, int> dfs(int x, bool c, int f, int s) { // 전체 갯수, 얼리어답터 수
    f += 1;
    if (c)
        s += 1;
    is_visit[x] = true;

    for (auto a : child[x]) {
        if (!is_visit[a]) {
            pair<int, int> tmp = dfs(a, !c, 0, 0);
            f += tmp.first;
            s += tmp.second;
        }
    }
    return {f, s};
}

void init() {
    cin >> n;
    int s, e;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e;
        child[s].push_back(e);
        child[e].push_back(s);
    }
    return;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!is_visit[i]) {
            pair<int, int> tmp = dfs(i, true, 0, 0);
            if (tmp.first == 1)
                ans += 1;
            else
                ans += min(tmp.second, tmp.first - tmp.second);
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}