#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> v;
vector<int> c;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        v.clear();
        c.clear();
        if (m == 0) {
            cout << 0 << '\n';
            continue;
        }
        for (int j = 0; j < m; j++) {
            string a, b;
            cin >> a >> b;
            int f = -1;
            for (int k = 0; k < v.size(); k++) {
                if (v[k] == b) {
                    f = k;
                    break;
                }
            }
            if (f != -1) {
                c[f] += 1;
            } else {
                v.push_back(b);
                c.push_back(2);
            }
        }

        long long ans = 1;
        for (int j = 0; j < c.size(); j++)
            ans *= c[i];

        cout << ans - 1 << '\n';
    }
}