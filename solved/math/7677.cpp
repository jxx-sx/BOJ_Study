#include <iostream>
#include <map>
#define mod (long long)10000

using namespace std;

map<long long, long long> mp;
long long n;

void get(long long x) {
    if (mp.find(x) != mp.end())
        return;
    if (x % 2) {
        get(x / 2 + 1);
        get(x / 2);
        long long a = mp.find(x / 2 + 1)->second;
        long long b = mp.find(x / 2)->second;
        mp.insert({x, (((a * a) % mod) + ((b * b) % mod)) % mod});
    } else {
        get(x / 2);
        get(x / 2 - 1);
        get(x / 2 + 1);
        long long a = mp.find(x / 2)->second;
        long long b = mp.find(x / 2 - 1)->second;
        long long c = mp.find(x / 2 + 1)->second;
        mp.insert({x, (a * ((b + c) % mod)) % mod});
    }
}

void init() {
    mp.insert({0, 0});
    mp.insert({1, 1});
    mp.insert({2, 1});
}

void solve() {
    while (true) {
        cin >> n;
        if (n == -1)
            break;
        get(n);
        cout << mp.find(n)->second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}