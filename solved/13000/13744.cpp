#include <iostream>
#include <vector>

#define N 1001
#define pb push_back

using namespace std;

int n, r, l;
int ord, scc_cnt, scc_l[2020], visited[2020], scc[2020];
vector<int> e[2020], square[N][N], st;

bool valid(int x, int y) {
    if (x < 1 or x > n)
        return false;
    if (y < 1 or y > n)
        return false;
    return true;
}

int dfs(int x) {
    visited[x] = scc_l[x] = ++ord;
    st.pb(x);
    for (auto a : e[x]) {
        if (!visited[a])
            scc_l[x] = min(scc_l[x], dfs(a));
        else if (!scc[a])
            scc_l[x] = min(scc_l[x], scc_l[a]);
    }
    if (scc_l[x] == visited[x]) {
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

    return scc_l[x];
}

void tarjan() {
    for (int i = 0; i < 2020; i++) {
        if (visited[i])
            continue;
        dfs(i);
    }
}

void init() {
    int a, b;
    cin >> n >> r >> l;
    for (int i = 0; i < l; i++) {
        cin >> a >> b;
        for (int j = 1; j <= r; j++) {
            if (!valid(a + j, b))
                break;
            for (auto k : square[a + j][b]) {
                if ((k & 1) == 0) {
                    e[i << 1].pb(k | 1);
                    e[k].pb(i << 1 | 1);
                }
            }
            square[a + j][b].pb(i << 1);
        }
        for (int j = 1; j <= r; j++) {
            if (!valid(a - j, b))
                break;
            for (auto k : square[a - j][b]) {
                if ((k & 1) == 0) {
                    e[i << 1].pb(k | 1);
                    e[k].pb(i << 1 | 1);
                }
            }
            square[a - j][b].pb(i << 1);
        }
        for (int j = 1; j <= r; j++) {
            if (!valid(a, b + j))
                break;
            for (auto k : square[a][b + j]) {
                if (k & 1) {
                    e[i << 1 | 1].pb(k ^ 1);
                    e[k].pb(i << 1);
                }
            }
            square[a][b + j].pb(i << 1 | 1);
        }
        for (int j = 1; j <= r; j++) {
            if (!valid(a, b - j))
                break;
            for (auto k : square[a][b - j]) {
                if (k & 1) {
                    e[i << 1 | 1].pb(k ^ 1);
                    e[k].pb(i << 1);
                }
            }
            square[a][b - j].pb(i << 1 | 1);
        }

        for (auto k : square[a][b]) {
            if (k & 1) {
                e[k].pb(i << 1);
                e[i << 1 | 1].pb(k ^ 1);
            } else {
                e[k].pb(i << 1 | 1);
                e[i << 1].pb(k ^ 1);
            }
        }
        square[a][b].pb(i << 1);
        square[a][b].pb(i << 1 | 1);
    }
}

void solve() {
    tarjan();
    for (int i = 0; i < l; i++) {
        if (scc[i << 1] == scc[i << 1 | 1]) {
            cout << 0;
            return;
        }
    }
    cout << 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}