#include <iostream>

using namespace std;

int n, arr[80000], cur, st[80000];
long long ans;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < n; i++) {
        while (cur and arr[st[cur - 1]] <= arr[i]) {
            ans += i - st[cur - 1] - 1;
            cur--;
        }
        st[cur] = i;
        cur++;
    }
    while (cur) {
        ans += n - st[cur - 1] - 1;
        cur--;
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