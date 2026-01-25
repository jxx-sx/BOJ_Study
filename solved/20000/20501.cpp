#include <bitset>
#include <iostream>
#include <string>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
bitset<2000> arr[2001];
int n, m, a, b;
string st;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> st;
        for (int j = 0; j < n; j++)
            if (st[j] == '1')
                arr[i][j] = true;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        cout << (arr[a] & arr[b]).count() << '\n';
    }

    return 0;
}