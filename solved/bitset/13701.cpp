#include <bitset>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
bitset<1 << 25> arr;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    int x;
    while (cin >> x) {
        if (arr[x])
            continue;
        arr[x] = true;
        cout << x << ' ';
    }

    return 0;
}