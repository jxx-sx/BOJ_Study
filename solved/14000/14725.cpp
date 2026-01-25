#include <iostream>
#include <map>
#include <string>

using namespace std;

int n;

struct Node {
    map<string, Node *> mp;
    Node *insert(string s) {
        auto tmp = mp.find(s);
        if (tmp != mp.end())
            return tmp->second;

        Node *node = new Node();
        mp.insert({s, node});

        return node;
    }
} *root;

void dfs(Node *x, int d = 0) {
    for (auto a : x->mp) {
        for (int i = 0; i < d; i++)
            cout << "--";
        cout << a.first;
        cout << '\n';
        dfs(a.second, d + 1);
    }
}

void init() {
    int m;
    string s;
    cin >> n;
    root = new Node();
    for (int i = 0; i < n; i++) {
        cin >> m;
        Node *cur = root;
        while (m--) {
            cin >> s;
            cur = cur->insert(s);
        }
    }
}

void solve() { dfs(root); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}