#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

long long arr[201][201];
int n, k;

void init() {
    cin >> n >> k;
    for (int i = 0; i <= n; i++)
        arr[i][1] = 1;
    for (int i = 0; i <= k; i++)
        arr[0][i] = 1;
    for (int i = 2; i <= k; i++)
        for (int l = 1; l <= n; l++)
            for (int j = 0; j <= l; j++) {
                arr[l][i] += arr[l - j][i - 1];
                arr[l][i] %= 1000000000;
            }
}

void solve() { cout << arr[n][k]; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}