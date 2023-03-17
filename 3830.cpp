#include <iostream>

using namespace std;
int n, m;
int p[100001];
int diff[100001];

int find_root(int x) {
    if (p[x] == x)
        return p[x];
    int rtn = find_root(p[x]);
    diff[x] += diff[p[x]];
    return p[x] = rtn;
}

int get_diff(int x) {
    if (p[x] == x)
        return 0;
    return get_diff(p[x]) + diff[x];
}

void union_root(int x, int y, int d) {
    x = find_root(x);
    p[x] = y;
    diff[x] = d;
}

bool init() {
    cin >> n >> m;
    if (n == 0 and m == 0)
        return false;

    for (int i = 1; i <= n; i++) {
        p[i] = i;
        diff[i] = 0;
    }

    return true;
}

void solve() {
    char mode;
    int a, b, w;
    for (int i = 0; i < m; i++) {
        cin >> mode;
        if (mode == '!') {
            cin >> a >> b >> w;
            union_root(a, b, w);
        } else {
            cin >> a >> b;
            int l = find_root(a);
            int r = find_root(b);
            if (l == r) {
                cout << get_diff(a) - get_diff(b) << '\n';
            } else
                cout << "UNKNOWN\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}