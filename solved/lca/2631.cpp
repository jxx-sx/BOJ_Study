#include <iostream>
#include <vector>

#define N 200
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, arr[N];
vector<int> v;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    v.pb(arr[0]);
    for (int i = 1; i < n; i++) {
        if (v.back() < arr[i])
            v.pb(arr[i]);
        else
            *lower_bound(v.begin(), v.end(), arr[i]) = arr[i];
    }
    cout << n - v.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}