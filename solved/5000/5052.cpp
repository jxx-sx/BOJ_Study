#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<string> v;

struct Node {
    bool end;
    Node *next[10];
    Node() : end(false) {
        for (int i = 0; i < 10; i++)
            next[i] = nullptr;
    }
};

struct Trie {
    Node *root;
    void init() { root = new Node(); }

    bool insert(string st) {
        Node *cur = root;
        for (auto a : st) {
            if (cur->end)
                return false;
            if (cur->next[a - '0'] == nullptr)
                cur = cur->next[a - '0'] = new Node();
            else
                cur = cur->next[a - '0'];
        }
        cur->end = true;
        return true;
    }
} trie;

void init() {
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v.begin(), v.end());

    trie.init();
}

void solve() {
    bool ans = true;
    for (auto a : v)
        ans &= trie.insert(a);
    cout << (ans ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}