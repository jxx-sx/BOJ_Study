#include <iostream>

using namespace std;

int n;
pair<int, int> arr[1000000]; // from, cnt;

void dp() {
    for (int i = 4; i <= n; i++) {
        arr[i].first = i - 1;
        arr[i].second = arr[i - 1].second + 1;
        if (i & 1) {
            if (arr[i >> 1].second + 1 < arr[i].second) {
                arr[i].first = i >> 1;
                arr[i].second = arr[i >> 1].second + 1;
            }
        }
        if (i % 3 == 0) {
            if (arr[i / 3].second + 1 < arr[i].second) {
                arr[i].first = i / 3;
                arr[i].second = arr[i / 3].second + 1;
            }
        }
    }
}

void print() {
    cout << arr[n].second << '\n';
    while (true) {
        cout << n << ' ';
        if (n == 1)
            break;
        n = arr[n].first;
    }
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