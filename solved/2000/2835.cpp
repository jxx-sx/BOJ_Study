#include <iostream>
#include <stdio.h>

using namespace std;

long long tree[86400 << 2];
long long lazy[86400 << 2];

void propagation(int s, int e, int i) {
    if (lazy[i] == 0)
        return;
    tree[i] += lazy[i] * (e - s + 1);
    if (s != e) {
        lazy[i << 1] += lazy[i];
        lazy[i << 1 | 1] += lazy[i];
    }
    lazy[i] = 0;
}

long long tree_update(int l, int r, int s, int e, int i) {
    propagation(s, e, i);
    if (e < l or r < s)
        return tree[i];
    if (l <= s and e <= r) {
        tree[i] += e - s + 1;
        if (s != e) {
            lazy[i << 1] += 1;
            lazy[i << 1 | 1] += 1;
        }
        return tree[i];
    }

    return tree[i] = tree_update(l, r, s, (s + e) / 2, i << 1) + tree_update(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

long long tree_query(int l, int r, int s, int e, int i) {
    propagation(s, e, i);
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];

    return tree_query(l, r, s, (s + e) / 2, i << 1) + tree_query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    int l, r, n;
    int hh, mm, ss, hhe, mme, sse;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d:%d:%d - %d:%d:%d", &hh, &mm, &ss, &hhe, &mme, &sse);
        l = 3600 * hh + 60 * mm + ss;
        r = 3600 * hhe + 60 * mme + sse;
        if (r < l) {
            tree_update(l, 86399, 0, 86399, 1);
            tree_update(0, r, 0, 86399, 1);
        } else
            tree_update(l, r, 0, 86399, 1);
    }

    return;
}

void solve() {
    int l, r, n;
    int hh, mm, ss, hhe, mme, sse;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d:%d:%d - %d:%d:%d", &hh, &mm, &ss, &hhe, &mme, &sse);
        l = 3600 * hh + 60 * mm + ss;
        r = 3600 * hhe + 60 * mme + sse;
        if (r < l)
            printf("%.10lf\n", ((double)tree_query(l, 86399, 0, 86399, 1) + (double)tree_query(0, r, 0, 86399, 1)) / ((86399 - l + 1) + (r - 0 + 1)));
        else
            printf("%.10lf\n", (double)tree_query(l, r, 0, 86399, 1) / (r - l + 1));
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}