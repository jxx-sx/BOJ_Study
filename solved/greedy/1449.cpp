#include <algorithm>
#include <iostream>

using namespace std;

int arr[1000];
int n, l;

void init() {
    cin >> n >> l;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
}

void solve() {
    int s = arr[0];
    int cnt = 1;
    for (int i = 1; i < n; i++) {
        if (s + l > arr[i])
            continue;
        s = arr[i];
        cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}