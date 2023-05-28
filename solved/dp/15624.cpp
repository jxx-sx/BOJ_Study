#include <iostream>

using namespace std;

int arr[1000001];

void init() {
    arr[0] = 0;
    arr[1] = 1;
    for (int i = 2; i < 1000001; i++)
        arr[i] = (arr[i - 1] + arr[i - 2]) % 1000000007;

    return;
}

void solve() {
    int n;
    cin >> n;
    cout << arr[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}