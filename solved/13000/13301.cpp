#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
int n, arr[82];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    arr[0] = arr[1] = 1;
    cin >> n;
    for (int i = 2; i <= n; i++)
        arr[i] = arr[i - 1] + arr[i - 2];
    cout << (arr[n] + arr[n - 1]) * 2;

    return 0;
}