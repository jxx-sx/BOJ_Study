#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int num[8];
int tmp[8];
int last_ans[8];
int n, m;

void back(int x, int d) {
    tmp[d] = x;
    if (d == m - 1) {
        for (int i = 0; i < m; i++) {
            if (last_ans[i] < num[tmp[i]])
                break;
            if (last_ans[i] > num[tmp[i]])
                return;
            if (i == m - 1)
                return;
        }

        for (int i = 0; i < m; i++)
            cout << (last_ans[i] = num[tmp[i]]) << ' ';
        cout << '\n';
        return;
    }

    for (int i = x; i < n; i++) {
        back(i, d + 1);
    }
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
        last_ans[i] = -1;
    }
    sort(num, num + n);
    return;
}

void solve() {
    for (int i = 0; i < n; i++)
        back(i, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}