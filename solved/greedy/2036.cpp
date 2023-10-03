#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<long long> v[2];
long long sum;
int n;

void init() {
    long long inp;
    cin >> n;
    while (n--) {
        cin >> inp;
        if (inp == 1) {
            sum++;
            continue;
        }
        v[inp > 0 ? 0 : 1].push_back(inp);
    }
    sort(v[0].begin(), v[0].end());
    sort(v[1].begin(), v[1].end(), greater());
}

void solve() {
    for (int i = 0; i < 2; i++)
        while (v[i].size() >= 2) {
            long long tmp = v[i].back();
            v[i].pop_back();
            sum += v[i].back() * tmp;
            v[i].pop_back();
        }
    if (v[0].size())
        sum += v[0].back();
    if (v[1].size())
        sum += v[1].back();
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}