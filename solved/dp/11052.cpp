#include <iostream>

using namespace std;
int n;
int arr[1010];

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= i / 2; j++)
            arr[i] = max(arr[i], arr[j] + arr[i - j]);

    cout << arr[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}