#include <iostream>
#include <vector>

#define N 6060
#define pb push_back

using namespace std;

int frog[3030][4];
int frog_lotus[3030][2];
int n, m, ord, scc_cnt, ans[3030];
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
        cin >> frog[i][0] >> frog[i][1] >> frog[i][2] >> frog[i][3];

    for (int i = 1; i <= n; i++) {
        cin >> frog_lotus[i][0] >> frog_lotus[i][1];
        lotus[frog_lotus[i][0]].pb(i << 1);
        lotus[frog_lotus[i][1]].pb(i << 1 | 1);
    }

    while (m--) {
        cin >> a >> b >> t;
        for (auto l : lotus[a]) {
            for (auto r : lotus[b]) {
                if (frog[l >> 1][t - 1] != frog[r >> 1][t - 1]) {
                    e[l].pb(r ^ 1);
                    e[r].pb(l ^ 1);
                }
            }
        }
    }
}

void solve() {

    tarjan();

    for (int i = 1; i <= n; i++) {
        if (scc[i << 1] == scc[i << 1 | 1]) {
            cout << "NO";
            return;
        }
        ans[scc[i << 1] < scc[i << 1 | 1] ? frog_lotus[i][0] : frog_lotus[i][1]] = i;
    }

    cout << "YES\n";
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