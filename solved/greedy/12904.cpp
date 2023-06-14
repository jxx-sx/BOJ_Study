#include <iostream>
#include <string>

using namespace std;
string a, b;
void init() { cin >> a >> b; }

void solve() {
    int l = 0;
    int r = b.size() - 1;
    bool direction = true;
    while (a.size() != (r - l + 1)) {
        if (!direction) {
            if (b[l] == 'B')
                direction = true;
            l++;
        } else {
            if (b[r] == 'B')
                direction = false;
            r--;
        }
    }
    int cur = direction ? l : r;
    for (auto c : a) {
        if (c != b[cur]) {
            cout << 0;
            return;
        }
        cur += direction ? 1 : -1;
    }
    cout << 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}