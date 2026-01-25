#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    long long ans = 1;
    cin >> n >> k;
    n--;
    k--;
    k = min(n - k, k);
    for (int i = n - k + 1; i <= n; i++)
        ans *= i;
    for (int i = 2; i <= k; i++)
        ans /= i;
    cout << ans;

    return 0;
}