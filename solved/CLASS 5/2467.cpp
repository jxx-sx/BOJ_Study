#include <iostream>

using namespace std;

int arr[100000];
int n;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    return;
}

void solve() {
    int l = 0;
    int r = n - 1;
    int sum = 2000000000;
    pair<int, int> ans = {0, 0};
    while (l < r) {
        int tmp = arr[l] + arr[r];
        if (abs(tmp) < abs(sum)) {
            sum = tmp;
            ans.first = arr[l];
            ans.second = arr[r];
        }
        if (tmp > 0)
            r--;
        else
            l++;
    }
    cout << ans.first << ' ' << ans.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}