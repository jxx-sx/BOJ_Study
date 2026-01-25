#include <iostream>
#include <string>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

string st1, st2;

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

Bitset arr[26], prv, cur;

void init() {
    cin >> st1 >> st2;
    for (int i = 0; i < st2.size(); i++)
        arr[st2[i] - 'A'].set(i);
    prv.set(50047);
}

void solve() {
    for (auto a : st1) {
        cur = arr[a - 'A'] | prv;
        prv.shift();
        prv = cur ^ (cur & (cur - prv));
    }
    prv.reset(50047);

    cout << prv.count();
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}