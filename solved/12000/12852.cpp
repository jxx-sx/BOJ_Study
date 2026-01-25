#include <iostream>

using namespace std;

int n;
pair<int, int> arr[1000001]; // from, cnt;

void dp() {
    for (int i = 4; i <= n; i++) {
        arr[i].first = i - 1;
        arr[i].second = arr[i - 1].second + 1;
        if ((i & 1) == 0)
            arr[i] = arr[i >> 1].second + 1 < arr[i].second ? make_pair(i >> 1, arr[i >> 1].second + 1) : arr[i];
        if (i % 3 == 0)
            arr[i] = arr[i / 3].second + 1 < arr[i].second ? make_pair(i / 3, arr[i / 3].second + 1) : arr[i];
    }
}

void print() {
    cout << arr[n].second << '\n';
    while (n != 1) {
        cout << n << ' ';
        n = arr[n].first;
    }
    cout << 1;
}

void solve() {
    dp();
    print();
}

void init() {
    cin >> n;
    arr[3] = arr[2] = {1, 1};
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    return 0;
}