#include <iostream>
#include <string>

using namespace std;
string st;
int arr[10];
int sum;
void init() {
    cin >> st;
    return;
}

void solve() {
    for (auto a : st) {
        arr[a - '0']++;
        sum += a - '0';
    }
    if (sum % 3 != 0 or arr[0] == 0)
        cout << -1;
    else {
        for (int i = 9; i >= 0; i--)
            for (int j = 0; j < arr[i]; j++)
                cout << i;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    
    return 0;
}