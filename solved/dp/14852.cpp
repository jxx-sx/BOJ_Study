#include <iostream>
#define mod 1000000007

using namespace std;

int n;
long long arr[3][1000001];
long long get(int i) { return (arr[0][i] + arr[1][i] + arr[2][i]) % mod; }

void init() {
    cin >> n;
    arr[0][1] = arr[2][1] = 1;
    arr[0][2] = 3;
    arr[2][2] = 2;
    arr[1][2] = 2;
}

void solve() {
    for (int i = 3; i <= n; i++) {
        arr[2][i] = get(i - 1);
        arr[0][i] = (arr[2][i] + get(i - 2)) % mod;
        arr[1][i] = (get(i - 2) * 2 + arr[1][i - 1]) % mod;
    }
    cout << get(n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}