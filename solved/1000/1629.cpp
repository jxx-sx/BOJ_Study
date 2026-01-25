#include <cmath>
#include <iostream>

using namespace std;

long long solve(long long a, long long b, long long c) {
    for (int i = 0; i < b; i++) {
        a = a * a % c;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long a, b, c;
    cin >> a >> b >> c;
    a = a % c;
    long long temp = 1;
    while (b != 0) {
        for (int i = 0;; i++) {
            if (pow(2, i) > b) {
                temp *= solve(a, i - 1, c);
                temp %= c;
                b -= pow(2, i - 1);
                break;
            }
        }
    }
    cout << temp % c;
}