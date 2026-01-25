#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int w[21][21][21];

int get(int x, int y, int z) {
    if (x <= 0 or y <= 0 or z <= 0)
        return 1;
    if (x > 20 or y > 20 or z > 20)
        return get(20, 20, 20);
    if (w[x][y][z])
        return w[x][y][z];
    if (x < y and y < z)
        w[x][y][z] = get(x, y, z - 1) + get(x, y - 1, z - 1) - get(x, y - 1, z);
    else
        w[x][y][z] = get(x - 1, y, z) + get(x - 1, y - 1, z) + get(x - 1, y, z - 1) - get(x - 1, y - 1, z - 1);
    return w[x][y][z];
}

void solve() {
    int a, b, c;
    while (true) {
        cin >> a >> b >> c;
        if (a == -1 and b == -1 and c == -1)
            break;

        cout << "w(" << a << ", " << b << ", " << c << ") = " << get(a, b, c) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}