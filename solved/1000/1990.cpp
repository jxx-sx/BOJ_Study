#include <algorithm>
#include <iostream>
#include <vector>

#define N 100000001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int st, ed;
bool prime[10001];
int pal;
vector<int> v;

int trim(int x) {
    if (!x)
        return 0;
    while (x % 10 == 0)
        x /= 10;
    return x;
}

void is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (prime[i])
            continue;
        if (x % i)
            continue;
        return;
    }
    v.pb(x);
}

void init() {
    prime[0] = prime[1] = true;
    for (int i = 2; i <= 100; i++) {
        if (prime[i])
            continue;
        for (int j = i; i * j < 10001; j++)
            prime[i * j] = true;
    }

    for (int i = 0; i < 10; i++) {
        pal += i * 1000000 + i;
        for (int j = 0; j < 10; j++) {
            pal += j * 100000 + j * 10;
            for (int k = 0; k < 10; k++) {
                pal += k * 10000 + k * 100;
                for (int l = 0; l < 10; l++) {
                    pal += l * 1000;
                    is_prime(trim(pal));
                    pal -= l * 1000;
                }
                pal -= k * 10000 + k * 100;
            }
            pal -= j * 100000 + j * 10;
        }
        pal -= i * 1000000 + i;
    }
    v.pb(11);

    sort(v.begin(), v.end());
    cin >> st >> ed;
}

void solve() {
    for (auto i = lower_bound(v.begin(), v.end(), st); i < upper_bound(v.begin(), v.end(), ed); i++)
        cout << (*i) << '\n';
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}