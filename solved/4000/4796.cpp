#include <iostream>

using namespace std;

int l, p, v, t;

bool init() {
    cin >> l >> p >> v;
    if (l == 0 and p == 0 and v == 0)
        return false;
    return true;
}

void solve() {
    t++;
    cout << "Case " << t << ": ";
    cout << l * (v / p) + min(v % p, l) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}