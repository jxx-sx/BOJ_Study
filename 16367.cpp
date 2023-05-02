#include <iostream>
#include <vector>

using namespace std;

vector<int> edges[10001]; // R: 1 ~ 5000, B: 5001 ~ 10000
vector<int> st;
int scc[10001];
int k, n;
int ord[10001];
int l[10001];
int scc_cnt;
int dfs_cnt;
bool rb[5001];

int dfs(int x) {
    dfs_cnt++;
    ord[x] = l[x] = dfs_cnt;
    st.push_back(x);

    for (auto a : edges[x]) {
        if (ord[a] == 0)
            l[x] = min(l[x], dfs(a));
        else if (scc[a] == 0)
            l[x] = min(l[x], l[a]);
    }

    if (ord[x] == l[x]) {
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
    for (int i = 1; i <= k; i++) {
        if (ord[i] == 0)
            dfs(i);
        if (ord[i + 5000] == 0)
            dfs(i + 5000);
    }
}

void init() {
    cin >> k >> n;
    int l1, l2, l3;
    char c1, c2, c3;

    for (int i = 0; i < n; i++) {
        cin >> l1 >> c1 >> l2 >> c2 >> l3 >> c3;
        edges[l1 + (c1 == 'R' ? 5000 : 0)].push_back(l2 + (c2 == 'R' ? 0 : 5000));
        edges[l1 + (c1 == 'R' ? 5000 : 0)].push_back(l3 + (c3 == 'R' ? 0 : 5000));
        edges[l2 + (c2 == 'R' ? 5000 : 0)].push_back(l1 + (c1 == 'R' ? 0 : 5000));
        edges[l2 + (c2 == 'R' ? 5000 : 0)].push_back(l3 + (c3 == 'R' ? 0 : 5000));
        edges[l3 + (c3 == 'R' ? 5000 : 0)].push_back(l1 + (c1 == 'R' ? 0 : 5000));
        edges[l3 + (c3 == 'R' ? 5000 : 0)].push_back(l2 + (c2 == 'R' ? 0 : 5000));
    }

    tarjan();

    return;
}

void solve() {
    for (int i = 1; i <= k; i++) {
        if (scc[i] == scc[i + 5000]) {
            cout << -1;
            return;
        }
        rb[i] = scc[i] < scc[i + 1];
    }
    for (int i = 1; i <= k; i++)
        cout << (rb[i] ? 'R' : 'B');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}