#include <iostream>

#define MOD 1000000000

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

long long arr[101][10][1 << 10];
long long ans;
int n;

void init() {
    cin >> n;
    for (int i = 1; i < 10; i++)
        arr[1][i][1 << i] = 1;
}

void solve() {
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 1; k < (1 << 10); k++) {
                if (j > 0) {
                    arr[i][j][k | (1 << j)] += arr[i - 1][j - 1][k];
                    arr[i][j][k | (1 << j)] %= MOD;
                }
                if (j < 9) {
                    arr[i][j][k | (1 << j)] += arr[i - 1][j + 1][k];
                    arr[i][j][k | (1 << j)] %= MOD;
                }
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        ans += arr[n][i][(1 << 10) - 1];
        ans %= MOD;
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