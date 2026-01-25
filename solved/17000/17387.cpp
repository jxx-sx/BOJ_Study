#include <iostream>

using namespace std;

pair<long long, long long> a, b, c, d;

int ccw(pair<long, long> a, pair<long, long> b, pair<long, long> c) {
    long long rtn = a.first * b.second + b.first * c.second + c.first * a.second - b.first * a.second - c.first * b.second - a.first * c.second;
    return rtn > 0 ? 1 : (rtn == 0 ? 0 : -1);
}

void init() {
    cin >> a.first >> a.second >> b.first >> b.second;
    cin >> c.first >> c.second >> d.first >> d.second;
}

void solve() {
    int ccw1 = ccw(a, b, c) * ccw(a, b, d);
    int ccw2 = ccw(c, d, a) * ccw(c, d, b);

    if (ccw1 == 0 and ccw2 == 0) {
        if (a > b)
            swap(a, b);
        if (c > d)
            swap(c, d);
        if (c <= b && a <= d)
            cout << 1;
        else
            cout << 0;
    } else if (ccw1 <= 0 and ccw2 <= 0)
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