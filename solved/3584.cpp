#include <iostream>
#include <vector>

using namespace std;

int p[15][10001];
int n;
int depth[10001];
bool is_visit[10001];
vector<int> edges[10001];

void dfs(int x, int d) {
    is_visit[x] = true;
    depth[x] = d;
    for (auto a : edges[x])
        if (!is_visit[a])
            dfs(a, d + 1);
}

void init() {
    int s, e;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        is_visit[i] = false;
        edges[i].clear();
        p[0][i] = 0;
    }

    for (int i = 1; i < n; i++) {
        cin >> s >> e;
        p[0][e] = s;
        edges[s].push_back(e);
    }

    for (int i = 1; i < 15; i++)
        for (int j = 1; j <= n; j++)
            p[i][j] = p[i - 1][p[i - 1][j]];
    for (int i = 1; i <= n; i++)
        if (p[0][i] == 0) {
            dfs(i, 0);
            break;
        }

    return;
}

void solve() {
    int l, r;
    cin >> l >> r;
    if (depth[l] < depth[r])
        swap(l, r);
    int diff = depth[l] - depth[r];
    int tmp = 0;
    while (diff) {
        if (diff & 1) {
            l = p[tmp][l];
        }
        tmp++;
        diff >>= 1;
    }

    if (l == r) {
        cout << l << '\n';
        return;
    }

    for (int i = 14; i >= 0; i--) {
        if (p[i][l] != p[i][r]) {
            l = p[i][l];
            r = p[i][r];
        }
    }
    while (l != r) {
        l = p[0][l];
        r = p[0][r];
    }
    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        init();
        solve();
    }

    return 0;
}