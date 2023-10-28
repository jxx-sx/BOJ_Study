#include <cassert>
#include <iostream>
#include <vector>

#define pb push_back
#define N 505050

using namespace std;

int n, m, ans[N];
int ord, scc_cnt, visited[N], l[N], scc[N]; // scc
vector<int> e[N], st;

int dfs(int x) {
    visited[x] = l[x] = ++ord;
    st.pb(x);

    for (auto a : e[x]) {
        if (!visited[a])
            l[x] = min(l[x], dfs(a));
        else if (!scc[a])
            l[x] = min(l[x], l[a]);
    }

    if (l[x] == visited[x]) {
        scc_cnt++;
        while (true) {
            scc[st.back()] = scc_cnt;
            if (st.back() == x) {
                st.pop_back();
                break;
            }
            st.pop_back();
        }
    }

    return l[x];
}

void tarjan() {
    for (int i = 0; i < N; i++) {
        if (visited[i])
            continue;
        dfs(i);
    }
}

void bitwiseAND(int x, int y, int z) {
    for (int i = 0; i < 5; i++) {
        if ((1 << i) & z) {
            e[x * 10 + i].pb(x * 10 + i + 5);
            e[y * 10 + i].pb(y * 10 + i + 5);
        } else {
            e[x * 10 + i + 5].pb(y * 10 + i);
            e[y * 10 + i + 5].pb(x * 10 + i);
        }
    }
}

void bitwiseOR(int x, int y, int z) {
    for (int i = 0; i < 5; i++) {
        if ((1 << i) & z) {
            e[x * 10 + i].pb(y * 10 + i + 5);
            e[y * 10 + i].pb(x * 10 + i + 5);
        } else {
            e[x * 10 + i + 5].pb(x * 10 + i);
            e[y * 10 + i + 5].pb(y * 10 + i);
        }
    }
}

void init() {
    int a, x, y, z;
    char t;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        e[i * 10 + 3].pb(i * 10 + 9);
        e[i * 10 + 4].pb(i * 10 + 8);
        e[i * 10 + 7].pb(i * 10 + 8);
        e[i * 10 + 7].pb(i * 10 + 4);
        e[i * 10 + 8].pb(i * 10 + 4);
        e[i * 10 + 9].pb(i * 10 + 2);
        e[i * 10 + 9].pb(i * 10 + 3);

        cin >> a;
        if (!a)
            continue;
        for (int j = 0; j < 5; j++)
            e[i * 10 + j + ((1 << j) & a ? 0 : 5)].pb(i * 10 + j + ((1 << j) & a ? 5 : 0));
    }
    cin >> m;
    while (m--) {
        cin >> t >> x >> y >> z;
        if (t == '&')
            bitwiseAND(x, y, z);
        else
            bitwiseOR(x, y, z);
    }
}

void solve() {
    tarjan();

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 5; j++) {
            if (scc[i * 10 + j] == scc[i * 10 + j + 5]) {
                cout << 0;
                return;
            }
            if (scc[i * 10 + j] > scc[i * 10 + j + 5])
                ans[i] |= (1 << j);
            // cout << scc[i * 10 + j] << ' ' << scc[i * 10 + j + 5] << endl;
        }
        cout << i << ' ' << ans[i] << endl;
        assert(8 <= ans[i] and ans[i] <= 19);
    }

    cout << 1 << '\n';
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}