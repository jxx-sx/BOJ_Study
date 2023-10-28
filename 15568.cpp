#include <iostream>
#include <vector>

#define N 6060
#define pb push_back

using namespace std;

struct Frog {
    int preference[4];
    int a, b;
} frog[3030];

int n, m, ord, scc_cnt;
int l[N], visited[N], scc[N];
vector<int> e[N], lotus[3030], st;

int dfs(int x) {
    l[x] = visited[x] = ++ord;
    st.pb(x);

    for (auto a : e[x]) {
        if (!visited[a])
            l[x] = min(l[x], dfs(a));
        else if (!scc[a])
            l[x] = min(l[x], l[a]);
    }

    if (visited[x] == l[x]) {
        scc_cnt++;
        while (true) {
            scc[st.back()] = scc_cnt;
            if (x == st.back()) {
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

void init() {
    int a, b, t;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> frog[i].preference[0] >> frog[i].preference[1] >> frog[i].preference[2] >> frog[i].preference[3];

    for (int i = 1; i <= n; i++) {
        cin >> frog[i].a >> frog[i].b;
        lotus[frog[i].a].pb(i);
        if (frog[i].a != frog[i].b)
            lotus[frog[i].b].pb(i);
        else
            e[(i << 1) | 1].pb(i << 1);
    }

    while (m--) {
        cin >> a >> b >> t;
        for (auto l : lotus[a]) {
            for (auto r : lotus[b]) {
                if (frog[l].preference[t - 1] != frog[r].preference[t - 1]) {
                    e[(l << 1) | (frog[l].a == a ? 0 : 1)].pb((r << 1) | (frog[r].a == b ? 1 : 0));
                    e[(r << 1) | (frog[r].a == b ? 0 : 1)].pb((l << 1) | (frog[l].a == a ? 1 : 0));
                }
            }
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (lotus[i].empty()) {
            cout << "NO";
            return;
        }
        for (int j = 0; j < lotus[i].size(); j++)
            for (int k = j + 1; k < lotus[i].size(); k++) {
                e[(lotus[i][j] << 1) | (frog[lotus[i][j]].a == i ? 0 : 1)].pb((lotus[i][k] << 1) | (frog[lotus[i][k]].a == i ? 1 : 0));
                e[(lotus[i][k] << 1) | (frog[lotus[i][k]].a == i ? 0 : 1)].pb((lotus[i][j] << 1) | (frog[lotus[i][j]].a == i ? 1 : 0));
            }
    }

    tarjan();

    for (int i = 1; i <= n; i++) {
        if (frog[i].a == frog[i].b)
            continue;
        if (scc[i << 1] == scc[i << 1 | 1]) {
            cout << "NO";
            return;
        }
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++)
        cout << (scc[i << 1] < scc[i << 1 | 1] ? frog[i].a : frog[i].b) << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}