#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int k, n;
vector<int> v;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> k >> n;
    int tmp;
    for (int i = 0; i < k; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());
    int l = 1;
    int r = v.back();
    int ans = 0;
    while (l < k) {
        int m = (l + r) / 2;
        int cnt = 0;
        for (int i = 0; i < k; i++) {
            cnt += v[i] / m;
        }
        if (cnt == n) {
            ans = max(ans, m);
        }
        if (cnt > n) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    cout << ans;
}