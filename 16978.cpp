#include <iostream>
#include <queue>
#include <vector>

using namespace std;
struct Node {
    int o, k, i, j;
};

struct compare {
    bool operator()(Node a, Node b) { return a.k > b.k; }
};
long long tree[400000];
priority_queue<Node, vector<Node>, compare> pq;
vector<pair<int, long long>> save;
long long ans[100000];
int n, m;
int cur, cnt;

long long tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        return tree[i];
    }
    return tree[i] = tree_init(s, (s + e) / 2, i << 1) + tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void tree_update(int k, long long v, int s, int e, int i) {
    if (s == k and e == k) {
        tree[i] = v;
        return;
    }
    if ((s + e) / 2 < k)
        tree_update(k, v, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        tree_update(k, v, s, (s + e) / 2, i << 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

long long tree_find(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return tree_find(l, r, s, (s + e) / 2, i << 1) + tree_find(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    cin >> n;
    tree_init(1, n, 1);
    cin >> m;
    int a, b, c, d;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (a == 1)
            save.push_back({b, c});
        else {
            cin >> d;
            Node tmp;
            tmp.o = cnt;
            tmp.k = b;
            tmp.i = c;
            tmp.j = d;
            cnt++;
            pq.push(tmp);
        }
    }
    return;
}

void solve() {
    while (!pq.empty()) {
        Node cur_node = pq.top();
        pq.pop();
        for (int i = cur; i < cur_node.k; i++)
            tree_update(save[i].first, save[i].second, 1, n, 1);
        ans[cur_node.o] = tree_find(cur_node.i, cur_node.j, 1, n, 1);
    }

    for (int i = 0; i < cnt; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}