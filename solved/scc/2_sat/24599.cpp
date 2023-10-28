#include <iostream>
#include <vector>

using namespace std;

vector<int> edges[200]; // T:0 ~ 99, F: 100 ~ 199
vector<int> st;
char arr[100];
int n, k, ord_cnt, scc_cnt;
int l[200], ord[200], scc[200];
bool ans[100];

int dfs(int x) {
    l[x] = ord[x] = ++ord_cnt;
    st.push_back(x);

    for (auto a : edges[x]) {
        if (!ord[a])
            l[x] = min(l[x], dfs(a));
        else if (!scc[a])
            l[x] = min(l[x], l[a]);
    }

    if (ord[x] == l[x]) {
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

void tarjan_init() {
    ord_cnt = scc_cnt = 0;
    for (int i = 0; i < 200; i++)
        l[i] = ord[i] = scc[i] = 0;
}

void tarjan() {
    tarjan_init();

    for (int i = 0; i < k; i++) {
        if (ord[i] == 0)
            dfs(i);
        if (ord[i + 100] == 0)
            dfs(i + 100);
    }
}

void make_edge() {
    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k; j++)
            if (arr[i] != 'X' and arr[j] != 'X') {
                edges[i + (arr[i] == 'T' ? 0 : 100)].push_back(j + (arr[j] == 'T' ? 100 : 0));
                edges[j + (arr[j] == 'T' ? 0 : 100)].push_back(i + (arr[i] == 'T' ? 100 : 0));
            }
}

void init() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++)
            cin >> arr[j];
        make_edge();
    }

    return;
}

void solve() {
    for (int i = 0; i < k; i++) {
        tarjan();
        for (int j = 0; j < k; j++)
            if (scc[j] == scc[j + 100]) {
                cout << -1;
                return;
            }
        edges[i].push_back(i + 100);
        tarjan();
        for (int j = 0; j < k; j++)
            ans[i] |= scc[j] == scc[j + 100];
        if (ans[i])
            edges[i].pop_back();
    }

    for (int i = 0; i < k; i++)
        cout << (ans[i] ? 'T' : 'F');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}