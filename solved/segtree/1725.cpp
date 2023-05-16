#include <iostream>

using namespace std;

int n;
int arr[100001];
int tree[400000];
long long max_area;

void tree_init(int s, int e, int i) {
    if (s == e) {
        tree[i] = s;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);

    tree[i] = arr[tree[i << 1]] < arr[tree[i << 1 | 1]] ? tree[i << 1] : tree[i << 1 | 1];
}

int query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 100000;
    if (l <= s and e <= r)
        return tree[i];

    int min_l = query(l, r, s, (s + e) / 2, i << 1);
    int min_r = query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);

    return arr[min_l] < arr[min_r] ? min_l : min_r;
}

void get_area(int s, int e) {
    if (e < s)
        return;
    long long width = e - s + 1;
    int height_index = query(s, e, 0, n - 1, 1);

    max_area = max(max_area, width * arr[height_index]);

    get_area(s, height_index - 1);
    get_area(height_index + 1, e);
}

void init() {
    cin >> n;
    arr[100000] = 1000000001;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    tree_init(0, n - 1, 1);
}

void solve() {
    get_area(0, n - 1);
    cout << max_area << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();

    return 0;
}