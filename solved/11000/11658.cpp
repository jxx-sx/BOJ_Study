#include <iostream>

using namespace std;

long long tree[1025][1025];
int arr[1025][1025];
int n, m;

void update(int x, int y, int d) {
    while (y <= n) {
        int k = x;
        while (k <= n) {
            tree[k][y] += d;
            k += k & -k;
        }
        y += y & -y;
    }
}

long long sum(int x, int y) {
    long long ret = 0;
    while (y) {
        int k = x;
        while (k) {
            ret += tree[k][y];
            k -= k & -k;
        }
        y -= y & -y;
    }
    return ret;
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
            update(i, j, arr[i][j]);
        }
}

void solve() {
    int op, a, b, c, d;
    while (m--) {
        cin >> op;
        if (op) {
            cin >> a >> b >> c >> d;
            cout << sum(c, d) + sum(a - 1, b - 1) - sum(a - 1, d) - sum(c, b - 1) << '\n';
        } else {
            cin >> a >> b >> c;
            update(a, b, c - arr[a][b]);
            arr[a][b] = c;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}