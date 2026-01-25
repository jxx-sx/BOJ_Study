#include <iostream>

using namespace std;

int n, m;
int arr[101];

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        arr[i] = i;
}

void solve() {
    int a, b;
    while (m--) {
        cin >> a >> b;
        swap(arr[a], arr[b]);
    }
    for (int i = 1; i <= n; i++)
        cout << arr[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}