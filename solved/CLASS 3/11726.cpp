#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int arr[1001];
    arr[0] = 1;
    arr[1] = 1;
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        arr[i] = (arr[i - 1] + arr[i - 2]) % 10007;
    }
    cout << arr[n];
}