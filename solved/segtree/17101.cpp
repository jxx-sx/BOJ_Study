#include <iostream>
#include <vector>

#define N 500001

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int tree[N];
int p[N][20], dep[N], in[N], out[N];
int n, ord, cur = 1;
vector<int> c[N];

void update(int x) {
    while (x <= n) {
        tree[x]++;
        x += x & -x;
    }
}

int get(int x) {
    int ret = 0;
    while (x) {
        ret += tree[x];
        x -= x & -x;
    }
    return ret;
}

int get(int l, int r) { return get(r) - get(l - 1); }

void dfs(int x = 1) {
    in[x] = ++ord;
    for (auto a : c[x]) {
        dep[a] = dep[x] + 1;
        dfs(a);
    }
    out[x] = ord;
}

void dp() {
    for (int j = 1; j < 20; j++)
        for (int i = 1; i <= n; i++)
            p[i][j] = p[p[i][j - 1]][j - 1];
}

void init() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> p[i][0];
        c[p[i][0]].push_back(i);
    }
}

void solve() {
    dfs();
    dp();
    update(1);
    cout << 1;
    for (int i = 2; i <= n; i++) {
        update(in[i]);
        if (in[cur] <= in[i] and in[i] <= out[cur]) {
            int diff = dep[i] - dep[cur] - 1;
            int tmp = i;
            int j = 0;
            while (diff) {
                if (diff & 1)
                    tmp = p[tmp][j];
                diff >>= 1;
                j++;
            }
            if (get(in[tmp], out[tmp]) > (i >> 1))
                cur = tmp;
        } else {
            if ( get(in[cur], out[cur]) <= (i >> 1))
                cur = p[cur][0];
        }
        cout << ' ' << cur;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}