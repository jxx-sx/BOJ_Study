#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    int *arr;
    arr = new int[n + 1];
    arr[0] = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i + 1];
        arr[i + 1] += arr[i];
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        cout << arr[b] - arr[a - 1] << '\n';
    }
}