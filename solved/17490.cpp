#include <iostream>
#include <queue>

using namespace std;

int p[1000001];
int n, m;
long long k;
bool construction[1000001];
int cnt;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int find_root(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x != y) {
        p[x] = y;
        cnt--;
    }
}

void make_union() {
    for (int i = 1; i < n; i++) {
        if (!construction[i])
            union_root(i, i + 1);
    }
    if (!construction[n])
        union_root(1, n);
}

void add_construction(int s, int e) {
    if (s > e)
        swap(s, e);
    if (s == 1 and e == n) {
        construction[e] = true;
        return;
    }
    construction[s] = true;
}

bool kruskal() {
    long long cur_stone = 0;
    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        if (find_root(cur.second)) {
            union_root(cur.second, 0);
            cur_stone += cur.first;
            if (cur_stone > k)
                return false;
        }
    }
    return true;
}

void init() {
    int s, e;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        pq.push({s, i});
        p[i] = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        add_construction(s, e);
    }
    cnt = n;
    make_union();
    return;
}

void solve() {
    if (cnt == 1) {
        cout << "YES";
        return;
    }
    if (kruskal())
        cout << "YES";
    else
        cout << "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}