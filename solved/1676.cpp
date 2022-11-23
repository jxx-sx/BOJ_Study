#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int a = 0;
    for (int i = 1; i <= n / 5; i++) {
        if (i % 25 == 0)
            a += 3;
        else if (i % 5 == 0)
            a += 2;
        else
            a += 1;
    }
    cout << a;
}