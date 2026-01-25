#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool room[100001];
pair<int, int> key[100001];
int n, m;
vector<int> edges[200001];
int l[200001];
int ord[200001];
int scc[200001];
bool in_stack[200001];
stack<int> st;
int ord_cnt;
int scc_cnt;

void dfs(int x) {
    ord_cnt++;
    ord[x] = l[x] = ord_cnt;
    in_stack[x] = true;
    st.push(x);
    for (auto a : edges[x]) {
        if (ord[a] == 0) {
            dfs(a);
            l[x] = min(l[a], l[x]);
        } else if (in_stack[a])
            l[x] = min(l[a], l[x]);
    }

    int cur;
    if (l[x] == ord[x]) {
        scc_cnt++;
        while (true) {
            cur = st.top();
            st.pop();
            in_stack[cur] = false;
            scc[cur] = scc_cnt;
            if (cur == x)
                break;
        }
    }
}

void tarjan() {
    for (int i = 1; i <= (m << 1); i++)
        if (ord[i] == 0)
            dfs(i);
}

void init() {
    int k, tmp;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> room[i];

    for (int i = 1; i <= m; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> tmp;
            key[tmp].first == 0 ? (key[tmp].first = i) : (key[tmp].second = i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (room[i]) {
            edges[key[i].first].push_back(key[i].second);
            edges[key[i].second].push_back(key[i].first);
            edges[key[i].first + m].push_back(key[i].second + m);
            edges[key[i].second + m].push_back(key[i].first + m);
        } else {
            edges[key[i].first].push_back(key[i].second + m);
            edges[key[i].second].push_back(key[i].first + m);
            edges[key[i].first + m].push_back(key[i].second);
            edges[key[i].second + m].push_back(key[i].first);
        }
    }

    tarjan();

    return;
}

void solve() {
    for (int i = 1; i <= m; i++)
        if (scc[i] == scc[i + m]) {
            cout << 0;
            return;
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