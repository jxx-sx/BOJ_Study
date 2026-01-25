#include <iostream>
#include <vector>

using namespace std;
int n;
int arr[1000000];
int lis[1000000];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    return;
}

void solve() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            lis[0] = 1;
        } else {
            lis[arr[i]] = lis[arr[i] - 1] + 1;
        }
        ans = max(lis[arr[i]], ans);
    }

    cout << n - ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}