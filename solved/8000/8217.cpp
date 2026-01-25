#include <iostream>
#include <vector>

#define N 300001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int p[N], l[N], r[N], ans[N];
long long tree[N];
vector<int> mid[N];
int n, m, q;
vector<int> o[N];
struct Query {
    int l, r, a;
} qry[N];

void update(int i, int d) {
    while (i <= m) {
        tree[i] += d;
        i += i & -i;
    }
}

void update(int i) {
    if (qry[i].l <= qry[i].r) {
        update(qry[i].l, qry[i].a);
        update(qry[i].r + 1, -qry[i].a);
    } else {
        update(1, qry[i].a);
        update(qry[i].r + 1, -qry[i].a);
        update(qry[i].l, qry[i].a);
    }
}

long long get(int i) {
    long long ret = 0;
    while (i) {
        ret += tree[i];
        i -= i & -i;
    }
    return ret;
}

bool query(int i) {
    long long sum = 0;
    for (auto sector : o[i]) {
        sum += get(sector);
        if (sum >= p[i])
            return true;
    }
    return false;
}

void init() {
    int inp;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> inp;
        o[inp].pb(i);
    }
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    cin >> q;
    for (int i = 1; i <= q; i++)
        cin >> qry[i].l >> qry[i].r >> qry[i].a;
    for (int i = 1; i <= n; i++) {
        l[i] = 1;
        r[i] = q;
    }
}

void solve() {
    while (true) {
        for (int i = 0; i < N; i++) {
            mid[i].clear();
            tree[i] = 0;
        }
        bool flag = false;
        for (int i = 1; i <= n; i++) {
            if (l[i] <= r[i]) {
                mid[(l[i] + r[i]) >> 1].pb(i);
                flag = true;
            }
        }
        if (!flag)
            break;
        for (int i = 1; i <= q; i++) {
            update(i);
            for (auto a : mid[i]) {
                if (query(a)) {
                    ans[a] = i;
                    r[a] = i - 1;
                } else
                    l[a] = i + 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i])
            cout << ans[i] << '\n';
        else
            cout << "NIE\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}