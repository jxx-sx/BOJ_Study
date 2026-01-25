#include <iostream>
#include <vector>

using namespace std;
vector<int> sqaure, arr = vector<int>(50001, 0);
int n;

void dp(int x) {
    for (auto a : sqaure) {
        if (a > x)
            break;

        if (arr[x] == 0)
            arr[x] = arr[x - a] + 1;
        else
            arr[x] = min(arr[x], arr[x - a] + 1);
    }
}

void init() {
    for (int i = 1; i * i <= 50000; i++) {
        sqaure.push_back(i * i);
    }
    cin >> n;
    return;
}

void solve() {
    for (int i = 0; i <= n; i++)
        dp(i);

    cout << arr[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}