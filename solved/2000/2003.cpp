#include <iostream>

using namespace std;

int arr[10000];
long long sum;
int l = 0, r = -1;
int n;
long long m, ans;

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    while (true) {
        if (sum == m) {
            ans++;
        }
        if (sum < m) {
            r++;
            if (r == n)
                break;
            sum += arr[r];
        } else {
            sum -= arr[l];
            l++;
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}