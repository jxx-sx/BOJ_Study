#include <iostream>
#include <vector>

using namespace std;

int p[1000001][18];
vector<int> edges[100001];
int n, m;
int d = 0;
int dep[100001];
bool check[100001];

void dfs(int x) {
    check[x] = true;
    dep[x] = d;
    d++;
    for (auto i : edges[x]) {
        if (!check[i]) {
            p[i][0] = x;
            dfs(i);
        }
    }
    d--;
}

void dp() {
    for (int j = 1; j < 18; j++)
        for (int i = 1; i <= n; i++)
            p[i][j] = p[p[i][j - 1]][j - 1];
}

int lca(int a, int b) {
    if (dep[a] < dep[b])
        swap(a, b);
    int diff = dep[a] - dep[b];
    for (int i = 0; diff; i++) {
        if (diff & 1)
            a = p[a][i];
        diff >>= 1;
    }

    if (a == b)
        return a;
    for (int i = 17; i >= 0; i--) {
        if (p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    }
    return p[a][0];
}

void init() {
    int s, e;

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e;
        edges[s].push_back(e);
        edges[e].push_back(s);
    }

    dfs(1);
    dp();

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        cout << lca(s, e) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
}