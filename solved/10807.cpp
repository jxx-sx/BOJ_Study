#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int a, ans = 0;
    cin >> a;
    for (int i = 0; i < n; i++) {
        if (arr[i] == a)
            ans += 1;
    }
    cout << ans;
}