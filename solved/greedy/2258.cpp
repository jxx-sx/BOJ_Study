#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int weight, price;
    int sum;
    bool operator<(const Node &t) const {
        if (price == t.price)
            return weight > t.weight;
        return price < t.price;
    }
};

int n, m;
vector<Node> v;

void init() {
    cin >> n >> m;
    v.resize(n);
    for (auto &a : v)
        cin >> a.weight >> a.price;
}

void solve() {
    int ans = -1;
    sort(v.begin(), v.end());
    v[0].sum = v[0].price;
    for (int i = 1; i < n; i++) {
        v[i].weight += v[i - 1].weight;
        if (v[i].price == v[i - 1].price)
            v[i].sum += v[i - 1].sum;
        v[i].sum += v[i].price;
    }
    for (auto a : v) {
        if (a.weight >= m)
            ans = ans == -1 ? a.sum : min(ans, a.sum);
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
