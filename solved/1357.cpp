#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string a, b;
int aa, bb;

void init() { cin >> a >> b; }

void solve() {
    int cur = 1;
    for (auto c : a) {
        aa += (c - '0') * cur;
        cur *= 10;
    }
    cur = 1;
    for (auto c : b) {
        bb += (c - '0') * cur;
        cur *= 10;
    }
    aa += bb;
    a = to_string(aa);
    reverse(a.begin(), a.end());

    cout << stoi(a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}