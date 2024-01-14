#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

bool arr[1001];
int n;

void init() {
    cin >> n;
    arr[1] = arr[3] = arr[4] = true;
}

void solve() {
    for (int i = 5; i <= n; i++)
        arr[i] = !(arr[i - 1] and arr[i - 3] and arr[i - 4]);
    cout << (arr[n] ? "SK" : "CY");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}