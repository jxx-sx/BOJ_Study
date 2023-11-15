#include <iostream>
#include <string>

using namespace std;

string s, p;

void init() { cin >> s >> p; }

void solve() {
    int n = 1, ans = 0;
    size_t tmp = 0;
    while (p != "") {
        if (s.find(p) != string::npos) {
            ans++;
            break;
        }
        tmp = s.find(p.substr(0, n), tmp);
        if (tmp != string::npos) {
            n++;
            continue;
        }
        ans++;

        p = p.substr(n - 1, p.size() - n + 1);
        tmp = 0;
        n = 1;
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