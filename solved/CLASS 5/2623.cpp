#include <iostream>
#include <queue>
#include <vector>

#define N 1001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<int> e[N], ans;
int n, m, b, c, k, in[N];

void init() {
    cin >> n >> m;
    while (m--) {
        cin >> k;
        cin >> b;
        for (int i = 1; i < k; i++) {
            cin >> c;
            e[b].pb(c);
            b = c;
            in[c]++;
        }
    }
}

void solve() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i])
            continue;
        q.push(i);
        ans.pb(i);
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto a : e[cur]) {
            in[a]--;
            if (in[a])
                continue;
            q.push(a);
            ans.pb(a);
        }
    }

    if (ans.size() != n)
        cout << 0;
    else
        for (auto a : ans)
            cout << a << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}