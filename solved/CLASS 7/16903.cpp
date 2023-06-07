#include <iostream>

using namespace std;

struct Node {
    int cnt;
    Node *n0, *n1;

    Node() {
        cnt = 0;
        n0 = n1 = nullptr;
    }

    Node(bool f) {
        cnt = 0;
        n0 = n1 = nullptr;
    }
} *root;

void add(Node *cur, int x, int d) {
    cur->cnt++;
    if (d == 32)
        return;

    if ((1 << (31 - d)) & x) {
        if (cur->n1 == nullptr)
            cur->n1 = new Node;
        add(cur->n1, x, d + 1);
    } else {
        if (cur->n0 == nullptr)
            cur->n0 = new Node;
        add(cur->n0, x, d + 1);
    }
}

void pop(Node *cur, int x, int d) {
    cur->cnt--;
    if (d == 32)
        return;

    if ((1 << (31 - d)) & x) {
        if (cur->n1->cnt == 1) {
            cur->n1 = nullptr;
            return;
        }
        pop(cur->n1, x, d + 1);
    } else {
        if (cur->n0->cnt == 1) {
            cur->n0 = nullptr;
            return;
        }
        pop(cur->n0, x, d + 1);
    }
}
int query(Node *cur, int x, int d) {
    if (d == 32)
        return 0;
    if (cur->n0 == nullptr)
        return (1 << (31 - d)) | query(cur->n1, x, d + 1);
    if (cur->n1 == nullptr)
        return query(cur->n0, x, d + 1);
    if ((1 << (31 - d)) & x)
        return query(cur->n0, x, d + 1);
    else
        return (1 << (31 - d)) | query(cur->n1, x, d + 1);
}
void init() {
    root = new Node();
    add(root, 0, 0);
}

void solve() {
    int m, q, x;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q >> x;
        if (q == 1)
            add(root, x, 0);
        else if (q == 2)
            pop(root, x, 0);
        else
            cout << (x ^ query(root, x, 0)) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}