#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    int n, k, cnt = 0;
    cin >> n >> k;
    while (__builtin_popcount(n) > k) {
        n++;
        cnt++;
    }
    cout << cnt;

    return 0;
}