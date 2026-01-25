#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long tree[101010];
long long arr[101010];
vector<int> comp;
int n, s;
vector<int> v;

void update(int x, int d) {
    while (x <= n) {
        tree[x] += d;
        x += x & -x;
    }
}

int sum(int x) {
    int ret = 0;
    while (x > 0) {
        ret += tree[x];
        x -= x & -x;
    }
    return ret;
}

void init() {
    cin >> n >> s;
    v.resize(n);
    comp.resize(n);
    for (auto &a : v) {
        cin >> a;
    }
    for (int i = 0; i < n; i++)
        comp[i] = v[i];
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++)
        comp[i] = lower_bound(v.begin(), v.end(), comp[i]) - v.begin() + 1;
}

void solve() {
    long long ans = 0;
    long long tmp = 0;
    for (int i = 0; i < s; i++) {
        tmp += sum(comp[i] - 1);
        update(comp[i], 1);
    }
    ans = tmp;

    for (int i = s; i < n; i++) {
        tmp -= sum(n) - sum(comp[i - s]);
        update(comp[i - s], -1);
        tmp += sum(comp[i] - 1);
        update(comp[i], 1);
        ans = max(ans, tmp);
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