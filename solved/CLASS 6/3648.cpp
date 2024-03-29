#include <iostream>
#include <stack>
#include <vector>

using namespace std;

stack<int> st;
int scc[1999];
int dfs_cnt, scc_cnt;
int l[1999];
int order[1999];
vector<int> edges[1999];
int n, m;

void dfs(int x) {
    dfs_cnt++;
    st.push(x);
    order[x] = l[x] = dfs_cnt;
    for (auto a : edges[x]) {
        if (order[a] == 0) {
            dfs(a);
            l[x] = min(l[a], l[x]);
        } else if (scc[a] == 0)
            l[x] = min(l[a], l[x]);
    }

    if (l[x] == order[x]) {
        scc_cnt++;
        while (true) {
            scc[st.top()] = scc_cnt;
            if (st.top() == x) {
                st.pop();
                break;
            }
            st.pop();
        }
    }
}

void get_scc() {
    for (int i = 1; i < (n << 1 | 1); i++)
        if (order[i] == 0)
            dfs(i);
}

void init() {
    int a, b, na, nb;
    scc_cnt = dfs_cnt = 0;
    for (int i = 1; i < (n << 1 | 1); i++) {
        scc[i] = l[i] = order[i] = 0;
        edges[i].clear();
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        if (a < 0) {
            na = -a;
            a = -a + n;
        } else
            na = a + n;
        if (b < 0) {
            nb = -b;
            b = -b + n;
        } else
            nb = b + n;

        edges[na].push_back(b);
        edges[nb].push_back(a);
    }
    edges[1 + n].push_back(1);

    get_scc();
    return;
}

void solve() {
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[i + n]) {
            cout << "no\n";
            return;
        }

    cout << "yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n >> m) {
        init();
        solve();
    }

    return 0;
}