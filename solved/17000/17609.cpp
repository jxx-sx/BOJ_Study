#include <iostream>
#include <string>

using namespace std;

int n;
string st;
int query(int s, int e, int d = 0) {
    if (s > e or d >= 2)
        return d;
    if (st[s] == st[e])
        return query(s + 1, e - 1, d);
    else {
        return min(query(s + 1, e, d + 1), query(s, e - 1, d + 1));
    }
}

void solve() {
    cin >> n;
    while (n--) {
        cin >> st;
        cout << query(0, st.size() - 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}