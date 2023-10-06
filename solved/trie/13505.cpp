#include <iostream>
#define MSB 536870912

using namespace std;

struct Node {
    Node *l, *r; // l = 0, r = 1
    Node() : l(nullptr), r(nullptr) {}
};

struct Trie {
    Node *root;
    void insert(int x) {
        Node *cur = root;
        int i = MSB;
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

    int query(int x) {
        Node *cur = root;
        int i = MSB;
        int ret = 0;
        while (i) {
            if (!cur->r) {
                cur = cur->l;
            } else if (!cur->l) {
                ret |= i;
                cur = cur->r;
            } else {
                if (!(x & i))
                    ret |= i;
                cur = x & i ? cur->l : cur->r;
            }
            i >>= 1;
        }
        return ret;
    }
} trie;

int n, ans, arr[100000];

void init() {
    cin >> n;
    trie.root = new Node();
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < n; i++)
        trie.insert(arr[i]);
    for (int i = 0; i < n; i++)
        ans = max(ans, arr[i] ^ trie.query(arr[i]));
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}