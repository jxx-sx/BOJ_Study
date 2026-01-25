#include <iostream>

using namespace std;
int n, m;
pair<int, int> p[100001];

pair<int, int> find_root(int x) {
    if (p[x].first == x)
        return p[x];
    pair<int, int> tmp = find_root(p[x].first);
    p[x].first = tmp.first;
    p[x].second += tmp.second;

    return p[x];
}

void union_root(int x, int y, int diff) {
    pair<int, int> l = find_root(x);
    pair<int, int> r = find_root(y);
    if (l.first != r.first) {
        p[r.first].first = l.first;
        p[r.first].second = diff - (r.second - l.second);
    }
}

bool init() {
    cin >> n >> m;
    if (n == 0 and m == 0)
        return false;
    for (int i = 1; i <= n; i++)
        p[i] = {i, 0};
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
            pair<int, int> l = find_root(a);
            pair<int, int> r = find_root(b);

            if (l.first == r.first)
                cout << r.second - l.second << '\n';
            else
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