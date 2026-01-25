#include <iostream>

using namespace std;

int p[500000];
int n, m;

int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        p[i] = i;
    return;
}

void solve() {
    int s, e;
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        cin >> s >> e;
        if (ans == 0) {
            s = find_root(s);
            e = find_root(e);
            if (s != e)
                p[s] = e;
            else
                ans = i;
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}