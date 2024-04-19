#include <iostream>
#include <vector>

#define N (1 << 20)
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

inline int _g(int x, int y) { return (x << 11) | (y << 2); }
inline int _d(int x, int y) { return _g(x, y) | 2; }
inline int _u(int x, int y) { return _g(x - 1, y) | 2; }
inline int _r(int x, int y) { return _g(x, y); }
inline int _l(int x, int y) { return _g(x, y - 1); }
inline int _n(int i) { return i | 1; }

vector<int> v[N];
vector<int> st;
int ord[N], l[N], scc[N];
int _scc, _ord;
int n, m, b, w, tc;
char arr[502][502];

int dfs(int x) {
    l[x] = ord[x] = ++_ord;
    st.pb(x);
    for (auto a : v[x]) {
        if (!ord[a])
            l[x] = min(dfs(a), l[x]);
        else if (!scc[a])
            l[x] = min(l[a], l[x]);
    }
    if (l[x] == ord[x]) {
        _scc++;
        while (true) {
            scc[st.back()] = _scc;
            if (x == st.back()) {
                st.pop_back();
                break;
            }
            st.pop_back();
        }
    }
    return l[x];
}

inline void tarjan() {
    for (int i = 0; i < N; i++) {
        if (ord[i])
            continue;
        dfs(i);
    }
}

inline void solve() {
    if ((b << 1) != w) {
        cout << "NO\n";
        return;
    }
    tarjan();
    for (int i = 0; i < N; i += 2) {
        if (scc[i] == scc[_n(i)]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

inline void init() {
    b = w = _scc = _ord = 0;
    for (int i = 0; i < N; i++) {
        v[i].clear();
        scc[i] = l[i] = ord[i] = 0;
    }
    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++) {
            if (0 < i and i <= n and 0 < j and j <= m)
                cin >> arr[i][j];
            else
                arr[i][j] = '.';
        }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 'W') {
                w++;
                v[_u(i, j)].pb(_n(_d(i, j)));
                v[_u(i, j)].pb(_n(_l(i, j)));
                v[_u(i, j)].pb(_n(_r(i, j)));
                v[_d(i, j)].pb(_n(_u(i, j)));
                v[_d(i, j)].pb(_n(_l(i, j)));
                v[_d(i, j)].pb(_n(_r(i, j)));
                v[_l(i, j)].pb(_n(_u(i, j)));
                v[_l(i, j)].pb(_n(_d(i, j)));
                v[_l(i, j)].pb(_n(_r(i, j)));
                v[_r(i, j)].pb(_n(_u(i, j)));
                v[_r(i, j)].pb(_n(_d(i, j)));
                v[_r(i, j)].pb(_n(_l(i, j)));
            }
            if (arr[i][j] == 'B') {
                b++;
                bool t1 = arr[i + 1][j] == 'W';
                bool t2 = arr[i - 1][j] == 'W';
                if (t1 && t2) {
                    v[_u(i, j)].pb(_n(_d(i, j)));
                    v[_n(_u(i, j))].pb(_d(i, j));
                    v[_d(i, j)].pb(_n(_u(i, j)));
                    v[_n(_d(i, j))].pb(_u(i, j));
                } else if (t1) {
                    v[_u(i, j)].pb(_n(_u(i, j)));
                    v[_n(_d(i, j))].pb(_d(i, j));
                } else if (t2) {
                    v[_n(_u(i, j))].pb(_u(i, j));
                    v[_d(i, j)].pb(_n(_d(i, j)));
                } else {
                    cout << "NO\n";
                    return;
                }

                t1 = arr[i][j + 1] == 'W';
                t2 = arr[i][j - 1] == 'W';
                if (t1 && t2) {
                    v[_l(i, j)].pb(_n(_r(i, j)));
                    v[_n(_l(i, j))].pb(_r(i, j));
                    v[_r(i, j)].pb(_n(_l(i, j)));
                    v[_n(_r(i, j))].pb(_l(i, j));
                } else if (t1) {
                    v[_l(i, j)].pb(_n(_l(i, j)));
                    v[_n(_r(i, j))].pb(_r(i, j));
                } else if (t2) {
                    v[_n(_l(i, j))].pb(_l(i, j));
                    v[_r(i, j)].pb(_n(_r(i, j)));
                } else {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }

    solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tc;
    while (tc--)
        init();

    return 0;
}

/*
19-11 x
10-2 y
1 dir
0 not
*/