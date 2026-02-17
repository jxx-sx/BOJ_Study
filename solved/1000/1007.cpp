#include <cmath>
#include <iostream>
#include <vector>
#define INF 1'000'000'000'000'000
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n;
int x[20], y[20];
long long mx, cur_x, cur_y;
int cnt1, cnt2;
bool b[20];
vector<int> st;

void dfs(int d = 0) {
    if (d == n) {
        mx = min(mx, cur_x * cur_x + cur_y * cur_y);
        return;
    }
    if (cnt1 < n / 2) {
        cur_x += x[d];
        cur_y += y[d];
        cnt1++;
        dfs(d + 1);
        cur_x -= x[d];
        cur_y -= y[d];
        cnt1--;
    }
    if (cnt2 < n / 2) {
        cur_x -= x[d];
        cur_y -= y[d];
        cnt2++;
        dfs(d + 1);
        cur_x += x[d];
        cur_y += y[d];
        cnt2--;
    }
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    mx = INF;
}

void solve() {
    dfs();
    cout << sqrt(mx) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cout << fixed;
    cout.precision(7);
    int tc;
    cin >> tc;
    while (tc--)
        init(), solve();

    return 0;
}