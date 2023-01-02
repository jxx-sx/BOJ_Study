#include <iostream>

using namespace std;
int arr[12];
int n;

void init() {
    cin >> n;
    arr[1] = 1;
    arr[2] = arr[1] + 1;
    arr[3] = arr[2] + arr[1] + 1;
    for (int i = 4; i < 12; i++)
        arr[i] = arr[i - 1] + arr[i - 2] + arr[i - 3];
}

void solve() {
    int inp;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        cout << arr[inp] << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}