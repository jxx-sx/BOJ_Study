#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
long long sumM = 0, sumC = 0;
vector<int> vM, vC;

void solve() {
    vector<int> v[sumC + 1];

    for (int i = 0; i < n + 1; i++)
        v[0].push_back(0);

    for (int j = 1; j <= sumC; j++) {
        for (int i = 0; i < n + 1; i++) {
            if (i == 0) {
                v[j].push_back(0);
                continue;
            }
            if (vC[i - 1] > j)
                v[j].push_back(v[j].back());
            else {
                int tmp;
                tmp = max(v[j - vC[i - 1]][i - 1] + vM[i - 1], v[j].back());
                if (tmp >= m) {
                    cout << j;
                    return;
                }
                v[j].push_back(tmp);
            }
        }
    }
}

void init() {
    int inp;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        vM.push_back(inp);
        sumM += inp;
    }

    for (int i = 0; i < n; i++) {
        cin >> inp;
        vC.push_back(inp);
        sumC += inp;
    }

    solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
}