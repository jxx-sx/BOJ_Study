#include <iostream>
#include <queue>

using namespace std;

int n, k, tmp;
queue<int> arr;

void init() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        arr.push(i + 1);
}

void solve() {
    cout << '<';
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < k - 1; j++) {
            arr.push(arr.front());
            arr.pop();
        }
        cout << arr.front() << ", ";
        arr.pop();
    }
    cout << arr.front() << '>';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}