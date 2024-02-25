#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

bool dp[1001];
int n;

void init() {
    cin >> n;
    dp[2] = true;
}

void solve() {
    for (int i = 4; i <= n; i++)
        dp[i] = !(dp[i - 1] | dp[i - 3]);
    cout << (dp[n] ? "SK" : "CY");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}