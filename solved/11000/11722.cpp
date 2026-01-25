#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> v;

void init() { cin >> n; }

void solve() {
    int inp;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        if (v.empty())
            v.push_back(-inp);
        else if (v.back() < -inp)
            v.push_back(-inp);
        else
            *lower_bound(v.begin(), v.end(), -inp) = -inp;
    }
    cout << v.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}