#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef unsigned long long ull;
const ull ULL_MSB = 1ull << 63;
#define BLOCKS_CNT (((N - 1) >> 6) + 1)
string str1, str2, ans;

struct Bitset {
    int N;
    ull blocks[782];

    inline void set(size_t pos) { blocks[pos >> 6] |= (1ULL << (pos & 63)); }
    inline void reset(size_t pos) { blocks[pos >> 6] &= ~(1ULL << (pos & 63)); }
    inline void toggle(size_t pos) { blocks[pos >> 6] ^= (1ULL << (pos & 63)); }
    inline int get(size_t pos) { return (blocks[pos >> 6] >> (pos & 63)) & 1; }

    inline void clear() {
        for (int i = 0; i < BLOCKS_CNT; i++)
            blocks[i] = 0;
    }

    inline void init(int x) { N = x; }

    vector<int> to_vector() {
        vector<int> v(N + 2);
        for (int i = 0; i < N; i++)
            v[i + 1] = v[i] + get(i);
        return v;
    }

    Bitset operator-(const Bitset &t) const {
        Bitset c(N);
        bool carry = false;
        for (int i = 0; i < BLOCKS_CNT; i++) {
            c.blocks[i] = blocks[i] - t.blocks[i];
            if (carry)
                c.blocks[i]--;
            carry = blocks[i] < t.blocks[i] || ((blocks[i] == t.blocks[i]) & carry);
        }
        return c;
    }

    void shift() {
        for (int i = BLOCKS_CNT - 1; i > 0; i--) {
            blocks[i] <<= 1;
            if (blocks[i - 1] & ULL_MSB)
                blocks[i] |= 1;
        }
        blocks[0] <<= 1;
        blocks[0] |= 1;
    }

    Bitset operator&(const Bitset &t) {
        Bitset c(N);
        for (int i = 0; i < BLOCKS_CNT; i++)
            c.blocks[i] = blocks[i] & t.blocks[i];
        return c;
    }

    Bitset operator|(const Bitset &t) {
        Bitset c(N);
        for (int i = 0; i < BLOCKS_CNT; i++)
            c.blocks[i] = blocks[i] | t.blocks[i];
        return c;
    }

    Bitset operator^(const Bitset &t) {
        Bitset c(N);
        for (int i = 0; i < BLOCKS_CNT; i++)
            c.blocks[i] = blocks[i] ^ t.blocks[i];
        return c;
    }
    Bitset(int N = 0) : N(N) {}
};

Bitset cur(50000), prv(50000);
Bitset arr[26], rev_arr[26];

void hirschberg(int s1, int e1, int s2, int e2) {
    if (s1 > e1 || s2 > e2)
        return;

    if (s1 == e1) {
        for (int i = s2; i <= e2; i++) {
            if (str1[s1] == str2[i]) {
                ans += str1[s1];
                break;
            }
        }
        return;
    }

    int m = (s1 + e1) >> 1;
    int len = e2 - s2 + 1;
    for (int i = 0; i < 26; i++) {
        arr[i].init(len);
        arr[i].clear();
        rev_arr[i].init(len);
        rev_arr[i].clear();
    }

    for (int i = s2; i <= e2; i++)
        arr[str2[i] - 'A'].set(i - s2), rev_arr[str2[e2 - i + s2] - 'A'].set(i - s2);

    prv.init(len), cur.init(len);
    prv.clear();
    for (int i = s1; i <= m; i++) {
        cur = arr[str1[i] - 'A'] | prv;
        prv.shift();
        prv = cur ^ (cur & (cur - prv));
    }

    vector<int> upper = prv.to_vector();
    prv.clear();

    for (int i = e1; i >= m + 1; i--) {
        cur = rev_arr[str1[i] - 'A'] | prv;
        prv.shift();
        prv = cur ^ (cur & (cur - prv));
    }
    vector<int> lower = prv.to_vector();
    reverse(lower.begin(), lower.end());

    int mxv = -1;
    int h = -1;
    for (int i = s2 - 1; i <= e2; i++) {
        if (mxv <= upper[i - s2 + 1] + lower[i - s2 + 2]) {
            mxv = upper[i - s2 + 1] + lower[i - s2 + 2];
            h = i;
        }
    }
    hirschberg(s1, m, s2, h);
    hirschberg(m + 1, e1, h + 1, e2);
}

void init() { cin >> str1 >> str2; }

void solve() {
    hirschberg(0, str1.size() - 1, 0, str2.size() - 1);
    cout << ans.size() << '\n' << ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}