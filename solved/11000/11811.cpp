#include <iostream>

using namespace std;

int arr[1000];
int n;

void init() { cin >> n; }

void solve() {
    int bit;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> bit;
            arr[i] |= bit;
            arr[j] |= bit;
        }

    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}