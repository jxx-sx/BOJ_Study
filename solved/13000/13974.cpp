#include <iostream>

#define N 5001
#define INF 1'000'000'000'000'000'000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;
int n;
ll d[N][N];
int opt[N][N], c[N];

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        c[i] += c[i - 1];
    }
    for (int i = 2; i <= n; i++)
        d[i - 1][i] = c[i] - c[i - 2], opt[i - 1][i] = i - 1;
}

void solve() {
    for (int i = 2; i < n; i++) {
        for (int j = 1; j + i <= n; j++) {
            d[j][j + i] = INF;
            for (int k = opt[j][j + i - 1]; k <= opt[j + 1][j + i]; k++) {
                if (d[j][j + i] > d[j][k] + d[k + 1][j + i] + c[j + i] - c[j - 1])
                    d[j][j + i] = d[j][k] + d[k + 1][j + i] + c[j + i] - c[j - 1], opt[j][j + i] = k;
            }
        }
    }
    cout << d[1][n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}