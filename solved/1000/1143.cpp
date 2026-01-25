#include <algorithm>
#include <iostream>
#include <memory.h>
#include <vector>

#define pb push_back
#define N 51

using namespace std;

int n, dfs_ord, scc_ord, sum, cnt;
int cost[N], scc[N], l[N], ord[N], in[N], scc_cost[N];
vector<int> st, e[N], nans;

int dfs(int x) {
    l[x] = ord[x] = ++dfs_ord;
    st.pb(x);
    for (auto a : e[x]) {
        if (!ord[a])
            l[x] = min(l[x], dfs(a));
        else if (!scc[a])
            l[x] = min(l[x], l[a]);
    }

    if (l[x] == ord[x]) {
        ++scc_ord;
        while (true) {
            scc[st.back()] = scc_ord;
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
        if (ord[i])
            continue;
        dfs(i);
    }
}

void init() {
    char ch;

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> cost[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> ch;
            if (ch == 'Y')
                e[i].pb(j);
        }

    for (int i = 0; i < N; i++)
        scc_cost[i] = 1000;
}

void solve() {
    tarjan();

    for (int i = 0; i < n; i++) {
        for (auto a : e[i]) {
            if (scc[a] != scc[i]) {
                in[scc[a]]++;
            }
        }
        scc_cost[scc[i]] = min(scc_cost[scc[i]], cost[i]);
    }

    for (int i = 1; i <= scc_ord; i++) {
        if (in[i])
            continue;
        sum += scc_cost[i];
        cnt++;
    }

    for (int i = 0; i < n; i++) {
        if (in[scc[i]] == 0 and scc_cost[scc[i]] == cost[i]) {
            in[scc[i]] = 1;
            continue;
        }
        nans.pb(cost[i]);
    }

    sort(nans.begin(), nans.end());

    for (auto a : nans) {
        if (sum <= a * cnt)
            break;
        sum += a;
        cnt++;
    }
    cout << fixed;
    cout.precision(12);
    cout << (double)sum / cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}