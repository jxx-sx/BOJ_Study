#include <iostream>
#include <string>

using namespace std;
string a, b;

void init() {
    getline(cin, a);
    getline(cin, b);
    return;
}

void solve() {
    int ans = 0;
    if (a.size() >= b.size())
        for (int i = 0; i <= a.size() - b.size(); i++) {
            if (a.substr(i, b.size()) == b) {
                i += b.size() - 1;
                ans += 1;
            }
        }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}