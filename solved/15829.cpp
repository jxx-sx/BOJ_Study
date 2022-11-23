#include <cmath>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string str;
    long long ans = 0;
    long long tmp;
    cin >> n;
    cin >> str;
    for (int i = 0; i < n; i++) {w
        tmp = str[i] - 96;
        for (int j = 0; j < i; j++) {
            tmp *= 31;
            tmp %= 1234567891;
        }
        ans += tmp;
        ans %= tmp;
    }
    cout << ans;
}