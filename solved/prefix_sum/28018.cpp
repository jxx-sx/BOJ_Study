#include <iostream>

#define N 1000002
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[N];
int n, q, s, e;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s >> e;
        arr[s]++;
        arr[e + 1]--;
    }
    for (int i = 1; i < N; i++)
        arr[i] += arr[i - 1];
    cin >> q;
}

void solve() {
    while (q--) {
        cin >> s;
        cout << arr[s] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}