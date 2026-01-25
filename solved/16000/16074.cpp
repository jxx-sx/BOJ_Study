#include <algorithm>
#include <iostream>
#include <vector>

#define N 250000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Qry {
    int sx, sy, dx, dy, l, r, ans;
} qry[100000];
int n, m, q;
int arr[500][500], p[N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
vector<pair<int, int>> h[N];
vector<int> _h, mi[N];

int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a != b)
        p[a] = b;
}

inline int g(int x, int y) { return x * 500 + y; }

bool valid(int x, int y) {
    if (x < 0 || n <= x)
        return false;
    return 0 <= y && y < m;
}

inline int mx_height(int i) { return max(arr[qry[i].sx][qry[i].sy], arr[qry[i].dx][qry[i].dy]); }

void connect(int x, int y) {
    for (int i = 0; i < 4; i++) {
        if (!valid(x + dx[i], y + dy[i]))
            continue;
        if (arr[x + dx[i]][y + dy[i]] > arr[x][y])
            continue;
        union_root(g(x + dx[i], y + dy[i]), g(x, y));
    }
}

void init() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            _h.push_back(arr[i][j]);
        }
    sort(_h.begin(), _h.end());
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            h[lower_bound(_h.begin(), _h.end(), arr[i][j]) - _h.begin()].pb({i, j});

    for (int i = 0; i < q; i++) {
        cin >> qry[i].sx >> qry[i].sy >> qry[i].dx >> qry[i].dy;
        qry[i].r = _h.size() - 1;
        qry[i].sx--, qry[i].sy--, qry[i].dx--, qry[i].dy--;
    }
}

void solve() {
    while (true) {
        bool f = true;
        for (int i = 0; i < N; i++) {
            mi[i].clear();
            p[i] = i;
        }
        for (int i = 0; i < q; i++) {
            if (qry[i].l <= qry[i].r) {
                mi[(qry[i].l + qry[i].r) >> 1].pb(i);
                f = false;
            }
        }
        if (f)
            break;
        for (int i = 0; i < _h.size(); i++) {
            for (auto [x, y] : h[i])
                connect(x, y);
            for (auto a : mi[i]) {
                if (mx_height(a) <= _h[i] && find_root(g(qry[a].sx, qry[a].sy)) == find_root(g(qry[a].dx, qry[a].dy))) {
                    qry[a].r = i - 1;
                    qry[a].ans = _h[i];
                } else
                    qry[a].l = i + 1;
            }
        }
    }
    for (int i = 0; i < q; i++)
        cout << qry[i].ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}