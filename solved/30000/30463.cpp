#include <iostream>
#include <string>

using namespace std;

long long arr[1 << 11];
int n, k;

void init() {
    string inp;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        int cur = 0;
        for (auto a : inp)
            cur |= (1 << (a - '0'));
        arr[cur]++;
    }
}

void solve() {
    long long ans = 0;
    for (int i = 1; i < (1 << 10); i++) {
        for (int j = i + 1; j < (1 << 10); j++) {
            int tmp = i | j;
            int cnt = 0;
            while (tmp) {
                if (tmp & 1)
                    cnt++;
                tmp >>= 1;
            }
            if (cnt == k)
                ans += arr[i] * arr[j];
        }
        int tmp = i;
        int cnt = 0;
        while (tmp) {
            if (tmp & 1)
                cnt++;
            tmp >>= 1;
        }
        if (cnt == k)
            ans += (arr[i] * (arr[i] - 1)) >> 1;
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