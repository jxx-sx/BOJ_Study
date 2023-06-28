#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

long long sum;
long long arr[300000];
int n;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sum += arr[i];
    }
    sort(arr, arr + n);
}

void solve() {
    if (n) {
        for (int i = 0; i < round((double)n * 0.15); i++) {
            sum -= arr[i];
            sum -= arr[n - i - 1];
        }
        cout << round((double)sum / (n - round((double)n * 0.15) * 2));
    } else
        cout << 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}