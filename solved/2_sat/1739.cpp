#include <iostream>
#include <vector>

using namespace std;
int n, m, k;
vector<int> edges[4001]; // 상: (0, 1000], 하 : (1000, 2000], 좌 : (2000, 3000] 우 : (3000, 4000]
vector<int> st;
int l[4001];
int scc[4001];
int ord[4001];
int scc_cnt;
int ord_cnt;

int dfs(int x) {
    ord_cnt++;
    l[x] = ord[x] = ord_cnt;
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
    for (int i = 1; i < 4001; i++)
        if (ord[i] == 0)
            dfs(i);
}

void init() {
    int a, b, c, d;
    for (int i = 1; i < 4001; i++) {
        edges[i].clear();
        l[i] = scc[i] = ord[i] = 0;
    }
    scc_cnt = ord_cnt = 0;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        cin >> a >> b >> c >> d;
        if (a != c and b != d) {
            // 출발 가로 도로 역방향
            edges[a + (b < d ? 2000 : 3000)].push_back(b + (a < c ? 0 : 1000));
            edges[a + (b < d ? 2000 : 3000)].push_back(c + (b < d ? 3000 : 2000));
            // 출발 세로 도로 역방향
            edges[b + (a < c ? 1000 : 0)].push_back(a + (b < d ? 3000 : 2000));
            edges[b + (a < c ? 1000 : 0)].push_back(d + (a < c ? 0 : 1000));
            // 도착 가로 도로 역방향
            edges[c + (b < d ? 2000 : 3000)].push_back(a + (b < d ? 3000 : 2000));
            edges[c + (b < d ? 2000 : 3000)].push_back(d + (a < c ? 0 : 1000));
            // 도착 세로 도로 역방향
            edges[d + (a < c ? 1000 : 0)].push_back(b + (a < c ? 0 : 1000));
            edges[d + (a < c ? 1000 : 0)].push_back(c + (b < d ? 3000 : 2000));
        } else if (a != c)
            edges[b + (a < c ? 1000 : 0)].push_back(b + (a < c ? 0 : 1000)); // if 위로 이동을 해야한다면
        else if (b != d)
            edges[a + (b < d ? 2000 : 3000)].push_back(a + (b < d ? 3000 : 2000)); // if 우측으로 이동을 해야 한다면
    }

    tarjan();

    return;
}

void solve() {
    for (int i = 1; i < 1001; i++) {
        if (scc[i] == scc[i + 1000] or scc[i + 2000] == scc[i + 3000]) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        init();
        solve();
    }

    return 0;
}