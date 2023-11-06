#include <algorithm>
#include <iostream>
#include <vector>

#define N 100000
#define Mod 1000000007

using namespace std;

int n;
vector<pair<int, int>> v;

struct Node {
    long long arr[11];
    void cp(Node t) {}

    Node operator+(const Node &t) {
        Node ret;
        for (int i = 0; i < 11; i++)
            ret.arr[i] = (arr[i] + t.arr[i]) % Mod;
        return ret;
    }
};

struct Seg {
    Node tree[N << 2];

    Node get(int k, int s, int e, int i) {
        if (k < s)
            return Node();
        if (e <= k)
            return tree[i];
        return get(k, s, (s + e) / 2, i << 1) + get(k, (s + e) / 2 + 1, e, i << 1 | 1);
    }

    void update(int k, int s, int e, int i) {
        if (s == e) {
            auto t = get(k - 1, 0, n - 1, 1);
            tree[i].arr[0] = 1;
            for (int j = 0; j < 10; j++)
                tree[i].arr[j + 1] = t.arr[j];
            return;
        }
        if ((s + e) / 2 < k)
            update(k, (s + e) / 2 + 1, e, i << 1 | 1);
        else
            update(k, s, (s + e) / 2, i << 1);
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
} tree;

void init() {
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(v.begin(), v.end());
}

void solve() {
    for (auto a : v)
        tree.update(a.second, 0, n - 1, 1);
    cout << tree.tree[1].arr[10];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}