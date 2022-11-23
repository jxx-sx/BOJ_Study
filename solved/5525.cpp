#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n, m;
string s;
vector<int> v;

void solve() {
    int ans = 0;
    for (int i = 0; i < v.size(); i++) {
        if (n <= v[i]) {
            ans += v[i] - n + 1;
        }
    }
    cout << ans;
}

void init() {
    cin >> n >> m >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'I') {
            int count = 0;
            for (int j = 1; j <= (s.size() - i - 1) / 2; j++) {
                if (s[i + 2 * j - 1] == 'O' && s[i + 2 * j] == 'I') {
                    count += 1;
                } else {

                    break;
                }
            }
            if (count) {
                v.push_back(count);
            }
            i += count * 2;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}