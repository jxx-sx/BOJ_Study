#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> v;
int n;

void init() { cin >> n; }

void solve() {
    int a;
    for (int i = 0; i < n; i++) {
        cin >> a;
        if (v.empty() or v.back() < a) {
            v.push_back(a);
            continue;
        }
        *lower_bound(v.begin(), v.end(), a) = a;
    }
    cout << n - v.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}