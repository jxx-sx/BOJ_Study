#include <iostream>

using namespace std;
struct Node {
    int d;
    Node *l, *r;
    Node() : d(0), l(nullptr), r(nullptr) {}
    Node(int d) : d(d), l(nullptr), r(nullptr) {}
} *root;

void trav(Node *d) {
    if (d->l)
        trav(d->l);
    if (d->r)
        trav(d->r);
    cout << d->d << '\n';
}

void init() {
    int t;
    cin >> t;
    root = new Node(t);
    while (cin >> t) {
        Node *cur = root;
        while (true) {
            if (cur->d > t) {
                if (cur->l) {
                    cur = cur->l;
                    continue;
                } else {
                    cur->l = new Node(t);
                    break;
                }
            } else {
                if (cur->r) {
                    cur = cur->r;
                    continue;
                } else {
                    cur->r = new Node(t);
                    break;
                }
            }
        }
    }
}

void solve() { trav(root); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}