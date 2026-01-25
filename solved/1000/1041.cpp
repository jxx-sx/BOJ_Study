#include <iostream>

#define INF 10000001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

ll n, arr[6], mn1 = INF, mn2 = INF, mn3 = INF;

void init() {
    cin >> n;
    for (int i = 0; i < 6; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < 6; i++)
        mn1 = min(arr[i], mn1);

    mn2 = min(arr[0] + arr[1], mn2);
    mn2 = min(arr[0] + arr[2], mn2);
    mn2 = min(arr[0] + arr[3], mn2);
    mn2 = min(arr[0] + arr[4], mn2);
    mn2 = min(arr[1] + arr[5], mn2);
    mn2 = min(arr[2] + arr[5], mn2);
    mn2 = min(arr[3] + arr[5], mn2);
    mn2 = min(arr[4] + arr[5], mn2);
    mn2 = min(arr[1] + arr[2], mn2);
    mn2 = min(arr[1] + arr[3], mn2);
    mn2 = min(arr[2] + arr[4], mn2);
    mn2 = min(arr[3] + arr[4], mn2);

    mn3 = min(arr[0] + arr[1] + arr[2], mn3);
    mn3 = min(arr[0] + arr[1] + arr[3], mn3);
    mn3 = min(arr[0] + arr[2] + arr[4], mn3);
    mn3 = min(arr[0] + arr[3] + arr[4], mn3);
    mn3 = min(arr[1] + arr[2] + arr[5], mn3);
    mn3 = min(arr[1] + arr[3] + arr[5], mn3);
    mn3 = min(arr[2] + arr[4] + arr[5], mn3);
    mn3 = min(arr[3] + arr[4] + arr[5], mn3);

    if (n == 1) {
        ll sum = 0;
        ll mx = 0;
        for (int i = 0; i < 6; i++) {
            sum += arr[i];
            mx = max(arr[i], mx);
        }
        cout << sum - mx;
    } else
        cout << mn3 * 4 + mn2 * (4 + (n - 2) * 8) + mn1 * ((n - 2) * ((n - 2) * 5 + 4));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}