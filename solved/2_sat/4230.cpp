#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> edges[60]; // H: [0, 30) W: [30, 60)
vector<int> st;
int l[60];
int ord[60];
int scc[60];
int scc_cnt;
int ord_cnt;
bool ans[30];
int n, m;

int dfs(int x) {
    l[x] = ord[x] = ++ord_cnt;
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
    for (int i = 0; i < n; i++) {
        if (ord[i] == 0)
            dfs(i);
        if (ord[i + 30] == 0)
            dfs(i + 30);
    }
}

bool init() {
    string sa, sb;
    int a, b;

    cin >> n >> m;

    if (n == 0 and m == 0)
        return false;

    for (int i = 0; i < 60; i++) {
        l[i] = ord[i] = scc[i] = 0;
        edges[i].clear();
    }
    scc_cnt = ord_cnt = 0;
    edges[30].push_back(0);
    for (int i = 0; i < m; i++) {
        cin >> sa >> sb;
        a = stoi(sa.substr(0, sa.size() - 1));
        b = stoi(sb.substr(0, sb.size() - 1));
        edges[a + (sa.back() == 'h' ? 0 : 30)].push_back(b + (sb.back() == 'h' ? 30 : 0));
        edges[b + (sb.back() == 'h' ? 0 : 30)].push_back(a + (sa.back() == 'h' ? 30 : 0));
    }

    tarjan();

    return true;
}

void solve() {
    for (int i = 0; i < n; i++) {
        if (scc[i] == scc[i + 30]) {
            cout << "bad luck\n";
            return;
        }
        ans[i] = scc[i] < scc[i + 30];
    }
    for (int i = 1; i < n; i++)
        cout << i << (ans[i] ? "w " : "h ");
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}