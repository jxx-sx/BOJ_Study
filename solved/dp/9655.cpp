#include <iostream>

using namespace std;

bool arr[1001];
int n;

void init() {
    cin >> n;
    arr[1] = true;
    arr[3] = true;
    for (int i = 4; i <= n; i++)
        arr[i] = !(arr[i - 1] & arr[i - 3]);
}

void solve() { cout << (arr[n] ? "SK" : "CY"); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}