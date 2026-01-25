#include <algorithm>
#include <iostream>
#define ind 536870912
#define inf 1100000000

using namespace std;

int n, arr[200000];
long long ans;

struct Node {
    Node *l, *r;
};

struct Trie {
    Node *root;
    void insert(int x) {
        Node *cur = root;
        int i = ind;
        while (i) {
            if (x & i) {
                if (!cur->r)
                    cur->r = new Node();
                cur = cur->r;
            } else {
                if (!cur->l)
                    cur->l = new Node();
                cur = cur->l;
            }
            i >>= 1;
        }
    }

    void mst(int s, int e, int d, Node *cur) {

        if (d < 0)
            return;
        if (e <= s)
            return;
        if (cur->l and cur->r) {
            int m = s;
            int tmp = inf;
            ans += 1 << d;
            if (!d)
                return;
            while (!(arr[m] & (1 << d))) {
                tmp = min(tmp, get(arr[m], d - 1, cur->r));
                m++;
            }
            ans += tmp;
            mst(s, m - 1, d - 1, cur->l);
            mst(m, e, d - 1, cur->r);
        } else if (cur->l and d)
            mst(s, e, d - 1, cur->l);
        else if (cur->r and d)
            mst(s, e, d - 1, cur->r);
    }

    int get(int x, int d, Node *cur) {
        Node *a = x & (1 << d) ? cur->r : cur->l;
        Node *b = a == cur->l ? cur->r : cur->l;
        if (d)
            return get(x, d - 1, a ? a : b) | (a ? 0 : 1 << d);
        return a ? 0 : 1;
    }
} trie;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    trie.root = new Node();
}

void solve() {
    sort(arr, arr + n);
    for (int i = 0; i < n; i++)
        trie.insert(arr[i]);

    trie.mst(0, n - 1, 29, trie.root);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}