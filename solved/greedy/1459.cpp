#include <iostream>

using namespace std;

void init() { return; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long x, y, w, s;
    cin >> x >> y >> w >> s;

    cout << min(x, y) * min(w * 2, s) + (max(x, y) - min(x, y)) % 2 * w + (max(x, y) - min(x, y)) / 2 * min(w * 2, 2 * s);

    return 0;
}