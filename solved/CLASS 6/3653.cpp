#include <iostream>

using namespace std;

long long tree[200001];
int arr[200001];
int n, m;

long long sum(int i) {
    long long rtn = 0;
    while (i) {
        rtn += tree[i];
        i -= i & -i;
    }
    return rtn;
}

void update(int i, int d) {
    while (i <= n + m) {
        tree[i] += d;
        i += i & -i;
    }
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < 200001; i++)
        tree[i] = 0;
    for (int i = 1; i <= n; i++) {
        arr[i] = m + i;
        update(arr[i], 1);
    }
}

void solve() {
    int inp;
    for (int i = m; i > 0; i--) {
        cin >> inp;
        cout << sum(arr[inp] - 1) << ' ';
        update(arr[inp], -1);
        arr[inp] = i;
        update(arr[inp], 1);
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        init();
        solve();
    }

    return 0;
}