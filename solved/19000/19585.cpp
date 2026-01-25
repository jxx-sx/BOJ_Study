#include <iostream>
#include <map>
#include <string>
#include <unordered_set>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Node {
    bool ed;
    int arr[26];
} node[4000400];

int c, n, q, _i = 26;
bool ans;
string st;
unordered_set<string> s;

void build(int i, int d = 1) {
    if (d == st.size()) {
        node[i].ed = true;
        return;
    }
    if (!node[i].arr[st[d] - 'a'])
        node[i].arr[st[d] - 'a'] = ++_i;
    build(node[i].arr[st[d] - 'a'], d + 1);
}

void dfs(int i, int d = 1) {
    if (d == st.size())
        return;
    if (node[i].ed)
        if (s.find(st.substr(d)) != s.end()) {
            ans = true;
            return;
        }
    if (node[i].arr[st[d] - 'a'])
        dfs(node[i].arr[st[d] - 'a'], d + 1);
}

void init() {
    cin >> c >> n;
    for (int i = 0; i < c; i++)
        cin >> st, build(st[0] - 'a' + 1);
    for (int i = 0; i < n; i++)
        cin >> st, s.insert(st);
}

void solve() {
    cin >> q;
    while (q--) {
        cin >> st;
        ans = false;
        dfs(st[0] - 'a' + 1);
        cout << (ans ? "Yes\n" : "No\n");
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}