#include <iostream>
#include <string>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef unsigned long long ull;
struct Bitset {
    ull blocks[782];

    void set(size_t pos) { blocks[pos >> 6] |= (1ULL << (pos & 63)); }
    void reset(size_t pos) { blocks[pos >> 6] &= ~(1ULL << (pos & 63)); }
    void toggle(size_t pos) { blocks[pos >> 6] ^= (1ULL << (pos & 63)); }

    size_t count() {
        size_t __ret = 0;
        for (auto a : blocks)
            __ret += __builtin_popcountll(a);
        return __ret;
    }

    Bitset operator-(const Bitset &t) const {
        Bitset c;
        bool carry = false;
        for (int i = 0; i < 782; i++) {
            c.blocks[i] = blocks[i] - t.blocks[i];
            if (carry)
                c.blocks[i]--;
            carry = blocks[i] < t.blocks[i] || ((blocks[i] == t.blocks[i]) & carry);
        }
        return c;
    }
    void shift() {
        for (int i = 781; i > 0; i--) {
            blocks[i] <<= 1;
            if ((blocks[i - 1] >> 63) & 1)
                blocks[i] |= 1;
        }
        blocks[0] <<= 1;
        blocks[0] |= 1;
    }

    Bitset operator&(const Bitset &t) {
        Bitset c;
        for (int i = 0; i < 782; i++)
            c.blocks[i] = blocks[i] & t.blocks[i];
        return c;
    }

    Bitset operator|(const Bitset &t) {
        Bitset c;
        for (int i = 0; i < 782; i++)
            c.blocks[i] = blocks[i] | t.blocks[i];
        return c;
    }

    Bitset operator^(const Bitset &t) {
        Bitset c;
        for (int i = 0; i < 782; i++)
            c.blocks[i] = blocks[i] ^ t.blocks[i];
        return c;
    }
};

Bitset arr_pre[26], arr_post[26], prv, cur;
string st1, st2;
string pre1, pre2, post1, post2;
int idx;
char x, y;
vector<bool> is_prime(50001, true);

void init() {
    cin >> st1 >> st2 >> x >> y;
    for (int i = 0; i < st1.size(); i++) {
        if (st1[i] == x) {
            pre1 = st1.substr(0, i);
            post1 = st1.substr(i + 1);
            break;
        }
    }
    for (int i = 0; i < st2.size(); i++) {
        if (st2[i] == x) {
            pre2 = st2.substr(0, i);
            post2 = st2.substr(i + 1);
            break;
        }
    }

    for (int i = 0; i < pre2.size(); i++) {
        if (pre2[i] == x || pre2[i] == y)
            continue;
        arr_pre[pre2[i] - 'a'].set(i);
    }

    for (int i = 0; i < post2.size(); i++) {
        if (post2[i] == x || post2[i] == y)
            continue;
        arr_post[post2[i] - 'a'].set(i);
    }

    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= 50000; i++) {
        if (!is_prime[i])
            continue;
        for (int j = i * i; j <= 50000; j += i)
            is_prime[j] = false;
    }
}

int lcs(string &str, Bitset arr[]) {
    for (auto a : str) {
        cur = arr[a - 'a'] | prv;
        prv.shift();
        prv = cur ^ (cur & (cur - prv));
    }

    return prv.count();
}

void solve() {
    int ans = 1;
    for (int i = 0; i < st1.size(); i++) {
        if (st1[i] == x) {
            ans += lcs(pre1, arr_pre);
            for (auto &a : prv.blocks)
                a = 0;
            ans += lcs(post1, arr_post);
            break;
        }
    }
    if (ans == 1) {
        cout << -1;
        return;
    }
    while (ans) {
        if (is_prime[ans]) {
            cout << ans;
            return;
        }
        ans--;
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}