#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> v;
int arr[1000];
int n;
int dp[1000];

void LIS() {
    for (int i = 0; i < n; i++) {
        if (v.size() == 0 or v.back() < arr[i]) {
            v.push_back(arr[i]);
            dp[i] = v.size() - 1;
        } else {
            auto lb = lower_bound(v.begin(), v.end(), arr[i]);
            dp[i] = lb - v.begin();
            *lb = arr[i];
        }
    }

    v.clear();
    for (int i = n - 1; i >= 0; i--) {
        if (v.size() == 0 or v.back() < arr[i]) {
            v.push_back(arr[i]);
            dp[i] += v.size() - 1;
        } else {
            auto lb = lower_bound(v.begin(), v.end(), arr[i]);
            dp[i] += lb - v.begin();
            *lb = arr[i];
        }
    }
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    LIS();
    return;
}

void solve() {
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, dp[i]);
    cout << ans + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}