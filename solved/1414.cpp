#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int n;
priority_queue<pair<int, pair<int, int>>> edges;
int p[50];
long long ans;
int cnt;

int check_priority(char ch) {
    if (ch == '0')
        return 0;
    else if ('A' <= ch and ch <= 'Z')
        return ch - 'A' + 27;
    else
        return ch - 'a' + 1;
}

int find_root(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find_root(p[x]);
}

bool union_root(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x != y) {
        p[x] = y;
        return true;
    }
    return false;
}

void kruskal() {
    int d, s, e;
    while (!edges.empty()) {
        d = -edges.top().first;
        s = edges.top().second.first;
        e = edges.top().second.second;
        edges.pop();

        if (union_root(s, e)) {
            cnt += 1;
            ans -= d;
        }
        if (cnt == n - 1)
            break;
    }
}

void init() {
    char inp;
    int tmp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        p[i] = i;
        for (int j = 0; j < n; j++) {
            cin >> inp;
            tmp = check_priority(inp);
            if (tmp) {
                ans += tmp;
                edges.push({-tmp, {i, j}});
            }
        }
    }
}

void solve() {
    kruskal();
    if (cnt == n - 1)
        cout << ans;
    else
        cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}