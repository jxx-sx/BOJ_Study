#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
int red_p[1001], blue_p[1001];
vector<pair<int, int>> red, blue;

int find_root(int x, int p[]) {
    if (p[x] == x)
        return x;
    return p[x] = find_root(p[x], p);
}

bool union_root(int a, int b, int p[]) {
    a = find_root(a, p);
    b = find_root(b, p);
    p[a] = b;
    return a != b;
}

int red_mst() {
    int cnt = 0;
    int blue_cnt = 0;
    for (auto a : red) {
        if (!union_root(a.first, a.second, red_p))
            continue;
        cnt++;
        if (cnt == n - 1)
            return blue_cnt;
    }

    for (auto a : blue) {
        if (!union_root(a.first, a.second, red_p))
            continue;
        cnt++;
        blue_cnt++;
        if (cnt == n - 1)
            return blue_cnt;
    }

    return cnt < n - 1 ? -1 : blue_cnt;
}

int blue_mst() {
    int cnt = 0;
    int blue_cnt = 0;

    for (auto a : blue) {
        if (!union_root(a.first, a.second, blue_p))
            continue;
        cnt++;
        blue_cnt++;
        if (cnt == n - 1)
            return blue_cnt;
    }

    for (auto a : red) {
        if (!union_root(a.first, a.second, blue_p))
            continue;
        cnt++;
        if (cnt == n - 1)
            return blue_cnt;
    }

    return cnt < n - 1 ? -1 : blue_cnt;
}

int init() {
    red.clear();
    blue.clear();
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        red_p[i] = blue_p[i] = i;
    char c;
    int f, t;
    for (int i = 0; i < m; i++) {
        cin >> c >> f >> t;
        (c == 'R' ? red : blue).push_back({f, t});
    }
    return (n | m | k);
}

void solve() {
    int red_score = red_mst();
    int blue_score = blue_mst();
    if (red_score == -1 or blue_score == -1) {
        cout << "0\n";
        return;
    }
    cout << (red_score <= k and k <= blue_score ? "1\n" : "0\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}