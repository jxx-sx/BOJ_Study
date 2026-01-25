#include <iostream>
#include <string>

using namespace std;

string str;

bool check(string st) {
    if (st.size() == 1)
        return true;
    int s = 0, e = st.size() - 1;
    while (s < e) {
        if (st[s] != st[e])
            return false;
        s++;
        e--;
    }
    return check(st.substr(0, st.size() / 2)) and check(st.substr(st.size() - st.size() / 2, st.size() / 2));
}

void init() { cin >> str; }

void solve() { cout << (check(str) ? "AKARAKA" : "IPSELENTI"); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}