#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long arr[100] = {1, 1, 1, 2, 2, 3, 4, 5, 7, 9};
    for (int i = 10; i < 100; i++) {
        arr[i] = arr[i - 1] + arr[i - 5];
    }
    int n, tmp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        cout << arr[tmp - 1] << '\n';
    }
}