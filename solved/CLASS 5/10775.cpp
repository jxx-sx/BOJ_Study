#include <iostream>

using namespace std;
int G, P;
int p[100001];

int find_root(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    p[x] = y;
}

void init() {
    cin >> G >> P;
    for (int i = 1; i <= G; i++)
        p[i] = i;

    return;
}

void solve() {
    int inp;
    int cnt = 0;
    for (int i = 0; i < P; i++) {
        cin >> inp;
        inp = find_root(inp);
        if (inp) {
            cnt++;
            union_root(inp, inp - 1);
        } else {
            break;
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    return 0;
}