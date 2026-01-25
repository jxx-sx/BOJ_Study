#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, pair<int, int>> Node;
vector<int> child[1000001];
bool is_visit[1000001];
int ans, n;

Node dfs(int x) { // 전체 갯수, 내가 true일때 얼리어답터 수, false ...
    Node rtn = {1, {1, 0}};
    is_visit[x] = true;

    for (auto a : child[x]) {
        if (!is_visit[a]) {
            Node tmp = dfs(a);
            rtn.first += tmp.first;
            rtn.second.first += min(tmp.second.first, tmp.second.second);
            rtn.second.second += tmp.second.first;
        }
    }
    if (rtn.first == 1) // leaf
        return {1, {1, 0}};
    return rtn;
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
            Node tmp = dfs(i);
            if (tmp.first == 1)
                ans += 1;
            else
                ans += min(tmp.second.first, tmp.second.second);
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