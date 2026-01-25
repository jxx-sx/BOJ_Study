#include <iostream>

using namespace std;

int arr[1010101];
int n;

void init() {
    arr[0] = arr[1] = 1;
    cin >> n;
}

void solve() {
    for (int i = 2; i <= n; i++)
        arr[i] = (arr[i - 1] + arr[i - 2]) % 15746;
    cout << arr[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}