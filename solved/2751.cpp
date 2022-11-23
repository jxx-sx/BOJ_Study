#include <algorithm>
#include <iostream>

using namespace std;

int n;
int *arr;

void init() {
    arr = new int[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    init();
    sort(arr, arr + n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << '\n';
}