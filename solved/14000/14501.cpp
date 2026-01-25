#include <algorithm>
#include <iostream>

using namespace std;

int n;
long arr[20];
void init() {
    int a, b;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        arr[i] = max(arr[i], arr[i - 1]);
        cin >> a >> b;
        if (i + a - 1 <= n)
            arr[i + a] = max(arr[i + a], arr[i] + b);
    }
}

void solve() {
    sort(arr, arr + n + 2);
    cout << arr[n + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}