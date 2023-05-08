#include <iostream>
#include <vector>

using namespace std;

vector<int> edges[500001];
int p[500001];
int lazy[500001];
int salary[500001];
int n, m;

void propagate(int x) {
    if (lazy[x]) {
        for (auto a : edges[x]) {
            lazy[a] += lazy[x];
            salary[a] += lazy[x];
        }
        lazy[x] = 0;
    }
}

void quary_u(int x) {
    if (x != 1)
        quary_u(p[x]);
    propagate(x);
}

void init() {
    cin >> n >> m >> salary[1];

    for (int i = 2; i <= n; i++) {
        cin >> salary[i] >> p[i];
        edges[p[i]].push_back(i);
    }
    return;
}

void solve() {
    char ch;
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> ch >> a;
        if (ch == 'p') {
            cin >> b;
            lazy[a] += b;
        } else {
            quary_u(a);
            cout << salary[a] << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}