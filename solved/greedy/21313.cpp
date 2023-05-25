#include <iostream>

using namespace std;
int n;
void init() {
    cin >> n;
    return;
}

void solve() {
    for (int i = 0; i < n / 2; i++)
        cout << "1\n2\n";
    if (n % 2)
        cout << 3;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    return 0;
}