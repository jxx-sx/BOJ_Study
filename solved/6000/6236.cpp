#include <iostream>

using namespace std;

int n, m, mn = 1000000000;
int l = 0, r = 1000000000;
int arr[100000];

bool valid(int x) {
    int cnt = 0;
    int budget = 0;
    for (int i = 0; i < n; i++) {
        if (budget < arr[i]) {
            cnt++;
            budget = x;
        }
        budget -= arr[i];
    }

    return cnt <= m;
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        l = max(l, arr[i]);
    }
}

void solve() {
    int mm;
    while (l <= r) {
        mm = (l + r) >> 1;
        if (valid(mm)) {
            mn = min(mn, mm);
            r = mm - 1;
        } else {
            l = mm + 1;
        }
    }

    cout << mn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}