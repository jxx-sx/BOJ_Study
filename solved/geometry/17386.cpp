#include <iostream>

using namespace std;

pair<long long, long long> a, b, c, d;

int ccw(pair<long, long> a, pair<long, long> b, pair<long, long> c) {
    long long rtn = a.first * b.second + b.first * c.second + c.first * a.second - b.first * a.second - c.first * b.second - a.first * c.second;
    return rtn > 0 ? 1 : -1;
}

void init() {
    cin >> a.first >> a.second >> b.first >> b.second;
    cin >> c.first >> c.second >> d.first >> d.second;
}

void solve() {
    if (ccw(a, b, c) * ccw(a, b, d) < 0 and ccw(c, d, a) * ccw(c, d, b) < 0)
        cout << 1;
    else
        cout << 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}