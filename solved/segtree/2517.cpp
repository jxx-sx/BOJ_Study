#include <iostream>
#include <vector>

using namespace std;

vector<int> tree[2000000];
int arr[500001];
int ans[500001];
int n;

void tree_init(int s, int e, int i) {
    if (s == e) {
        tree[i].emplace_back(s);
        return;
    }

    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);

    int l = 0, r = 0;

    while (l < tree[i << 1].size() and r < tree[i << 1 | 1].size()) {
        if (arr[tree[i << 1][l]] > arr[tree[i << 1 | 1][r]]) {
            tree[i].emplace_back(tree[i << 1][l]);
            l++;
        } else {
            // cout << s << ' ' << e << ' ' << tree[i << 1 | 1][r] << endl;
            ans[tree[i << 1 | 1][r]] -= tree[i << 1].size() + r - tree[i].size();
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
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        ans[i] = i;
    }
    tree_init(1, n, 1);
    return;
}

void solve() {
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}