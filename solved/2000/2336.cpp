#include <algorithm>
#include <iostream>
#include <memory.h>

#define N 500001

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Score {
    int a, b, c;

    bool operator<(const Score &t) const { return a < t.a; }
} score[N];

int tree[N];
int n;

void update(int x, int d) {
    while (x <= n) {
        tree[x] = min(d, tree[x]);
        x += x & -x;
    }
}

int get(int x) {
    int ret = N;
    while (x) {
        ret = min(ret, tree[x]);
        x -= x & -x;
    }

    return ret;
}

void init() {
    fill(tree, tree + N, N);
    cin >> n;
    int t;
    for (int i = 1; i <= n; i++) {
        cin >> t;
        score[t].a = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> t;
        score[t].b = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> t;
        score[t].c = i;
    }
}

void solve() {
    int ans = 0;
    sort(score + 1, score + n + 1);
    for (int i = 1; i <= n; i++) {
        if (get(score[i].b) > score[i].c)
            ans++;
        update(score[i].b, score[i].c);
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