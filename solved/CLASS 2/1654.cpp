#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int k, n;
vector<long long> v;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> k >> n;
    long long tmp;
    for (int i = 0; i < k; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());

    long long l = 1;
    long long r = v.back();
    long long ans = 0;

    while (l <= r) {
        long long m = (l + r) / 2;
        long long cnt = 0;
        for (int i = 0; i < k; i++) {
            cnt += v[i] / m;
        }
        if (cnt >= n) {
            l = m + 1;
            ans = max(ans, m);

        } else {
            r = m - 1;
        }
    }
    cout << ans;
}