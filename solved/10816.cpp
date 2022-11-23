#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, tmp;
vector<int> arr;

void solve() {
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> tmp;
        cout << lower_bound(arr.begin(), arr.end(), tmp + 1) - lower_bound(arr.begin(), arr.end(), tmp) << ' ';
    }
}
void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        arr.push_back(tmp);
    }
    sort(arr.begin(), arr.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}