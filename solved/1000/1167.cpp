#include <iostream>
#include <vector>

using namespace std;

int n;
int ans;
bool is_visit[100001];
vector<pair<int, int>> edges[100001];

int dfs(int x) {
    int ret = 0, tmp;
    is_visit[x] = true;
    for (auto a : edges[x]) {
        if (!is_visit[a.first]) {
            tmp = dfs(a.first) + a.second;
            ans = max(ans, tmp + ret);
            ret = max(tmp, ret);
        }
    }
    return ret;
}

void init() {
    cin >> n;
    int a, b, v;
    for (int i = 0; i < n; i++) {
        cin >> v;
        while (true) {
            cin >> a;
            if (a == -1)
                break;
            cin >> b;
            edges[v].push_back({a, b});
        }
    }
    return;
}

void solve() {
    for (int i = 1; i <= n; i++)
        if (!is_visit[i])
            dfs(i);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}