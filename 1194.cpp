#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b, c, d, e, f, g = 0;
    cin >> a >> b >> c >> d >> e >> f;
    g += a + b + c + d + e + f - min(min(a, b), min(c, d)) - min(e, f);
    cout << g;
}