#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string arr[10000], cmp;
    int n, m;
    int ans = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    sort(arr, arr + n);
    for (int i = 0; i < m; i++) {
        cin >> cmp;
        if (binary_search(arr, arr + n, cmp))
            ans++;
    }

    cout << ans;
}