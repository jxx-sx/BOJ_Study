#include <iostream>

using namespace std;

void init() {
    int n;
    cin >> n;
    cout << (n & 1 ? "Goose" : "Duck");
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}