#include <iostream>
#include <vector>

using namespace std;

vector<int> tree[4000000];
long long ans;
int n;

void tree_init(int s, int e, int i) {
    if (s == e) {
        int inp;
        cin >> inp;
        tree[i].emplace_back(inp);
        return;
    }

    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);

    int l = 0, r = 0;

    while (l < tree[i << 1].size() and r < tree[i << 1 | 1].size()) {
        if (tree[i << 1][l] < tree[i << 1 | 1][r]) {
            tree[i].emplace_back(tree[i << 1][l]);
            l++;
        } else {
            ans += tree[i << 1].size() + r - tree[i].size();
            tree[i].emplace_back(tree[i << 1 | 1][r]);
            r++;
        }
    }

    while (l < tree[i << 1].size()) {
        tree[i].emplace_back(tree[i << 1][l]);
        l++;
    }

    while (r < tree[i << 1 | 1].size()) {
        tree[i].emplace_back(tree[i << 1 | 1][r]);
        r++;
    }
}

void init() {
    cin >> n;
    tree_init(0, n - 1, 1);
}

void solve() { cout << ans; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}