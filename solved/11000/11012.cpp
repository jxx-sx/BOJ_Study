#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
    Node *l, *r;
    int v;

    Node() {
        v = 0;
        l = r = nullptr;
    }
} head[100001];
int n, m;
pair<int, int> query[10001];
int cur_head;

void tree_init(int s, int e, Node *c) {
    if (s == e)
        return;
    c->l = new Node;
    c->r = new Node;
    tree_init(s, (s + e) / 2, c->l);
    tree_init((s + e) / 2 + 1, e, c->r);
}

void update(Node *cur, Node *prev, int k, int s, int e) {
    cur->v += 1;
    if (s == k and e == k)
        return;

    if (cur->l == nullptr) {
        cur->l = prev->l;
        cur->r = prev->r;
    }

    if (k > (s + e) / 2) {
        Node *tmp = new Node;
        tmp->l = cur->r->l;
        tmp->r = cur->r->r;
        tmp->v = cur->r->v;
        cur->r = tmp;

        update(cur->r, prev->r, k, (s + e) / 2 + 1, e);
    } else {
        Node *tmp = new Node;
        tmp->l = cur->l->l;
        tmp->r = cur->l->r;
        tmp->v = cur->l->v;
        cur->l = tmp;

        update(cur->l, prev->l, k, s, (s + e) / 2);
    }
}

int sum(int l, int r, int s, int e, Node *c) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return c->v;

    return sum(l, r, s, (s + e) / 2, c->l) + sum(l, r, (s + e) / 2 + 1, e, c->r);
}

void init() {
    tree_init(0, 100000, head);
    cur_head = 0;

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> query[i].second >> query[i].first;

    sort(query, query + n);

    for (int i = 0; i < n; i++) {
        while (cur_head < query[i].first) {
            head[cur_head + 1].l = head[cur_head].l;
            head[cur_head + 1].r = head[cur_head].r;
            head[cur_head + 1].v = head[cur_head].v;
            cur_head++;
        }
        update(&head[query[i].first], &head[query[i].first - 1], query[i].second, 0, 100000);
    }

    return;
}

void solve() {
    int l, r, b, t;
    long long ans = 0;
    while (m--) {
        cin >> l >> r >> b >> t;
        while (cur_head < t) {
            head[cur_head + 1].l = head[cur_head].l;
            head[cur_head + 1].r = head[cur_head].r;
            head[cur_head + 1].v = head[cur_head].v;
            cur_head++;
        }
        if (b > 0)
            ans += sum(l, r, 0, 100000, &head[t]) - sum(l, r, 0, 100000, &head[b - 1]);
        else {
            ans += sum(l, r, 0, 100000, &head[t]);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        init();
        solve();
    }

    return 0;
}