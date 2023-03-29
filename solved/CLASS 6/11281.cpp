#include <iostream>
#include <stack>
#include <vector>

using namespace std;

stack<int> st;
int scc[20001];
vector<int> edges[20001];
int dfs_order[20001];
int l[20001];
int dfs_cnt, scc_cnt;
bool ans[10001];
int n, m;

void dfs(int x) {
    dfs_cnt++;
    l[x] = dfs_order[x] = dfs_cnt;
    st.push(x);

    for (auto a : edges[x]) {
        if (dfs_order[a] == 0) {
            dfs(a);
            l[x] = min(l[x], l[a]);
        } else if (scc[a] == 0) {
            l[x] = min(l[x], l[a]);
        }
    }

    if (l[x] == dfs_order[x]) {
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
        if (dfs_order[i] == 0)
            dfs(i);
}

void init() {
    cin >> n >> m;
    int a, b, na, nb;
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

        edges[nb].push_back(a);
        edges[na].push_back(b);
    }

    get_scc();

    return;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[i + n]) {
            cout << 0;
            return;
        }
        ans[i] = scc[i] < scc[i + n] ? true : false;
    }

    cout << 1 << '\n';
    for (int i = 1; i <= n; i++)
        cout << (ans[i] ? 1 : 0) << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}