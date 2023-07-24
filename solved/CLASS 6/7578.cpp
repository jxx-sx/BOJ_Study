#include <algorithm>
#include <iostream>

using namespace std;
int n;
pair<int, int> arr[500001];
int coord[500001];
long long tree[500001];
int arr_b[500001];

void update(int i) {
    while (i <= n) {
        tree[i]++;
        i += i & -i;
    }
}

long long sum(int i) {
    long long rtn = 0;
    while (i) {
        rtn += tree[i];
        i -= i & -i;
    }
    return rtn;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first;
        arr[i].second = i + 1;
    }

    sort(arr, arr + n);
    for (int i = 0; i < n; i++)
        coord[i] = arr[i].first;

    for (int i = 0; i < n; i++) {
        cin >> arr_b[i];
        arr_b[i] = arr[lower_bound(coord, coord + n, arr_b[i]) - coord].second;
    }
}

void solve() {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += i - sum(arr_b[i]);
        update(arr_b[i]);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}