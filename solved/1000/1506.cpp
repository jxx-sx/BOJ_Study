#include <iostream>
#include <vector>
#define pb push_back

using namespace std;

int n, scc_cnt, dfs_cnt;
int arr[100], scc[100], l[100], ord[100];
vector<int> v[100], st, ans;

int dfs(int x) {
    ord[x] = l[x] = ++dfs_cnt;
    st.pb(x);
    for (auto a : v[x]) {
        if (!ord[a])
            l[x] = min(dfs(a), l[x]);
        else if (!scc[a])
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
    for (int i = 0; i < n; i++)
        if (!ord[i])
            dfs(i);
}

void init() {
    char ch;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> ch;
            if (ch == '1')
                v[i].pb(j);
        }
}

void solve() {
    tarjan();
    ans = vector(scc_cnt, 10101010);
    for (int i = 0; i < n; i++)
        ans[scc[i] - 1] = min(ans[scc[i] - 1], arr[i]);
    int sum = 0;
    for (auto a : ans)
        sum += a;
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}