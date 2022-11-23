#include <algorithm>
#include <iostream>

using namespace std;

int A[100000], n, m;

int find(int target) {
    int lo, hi, mid;
    lo = 0;
    hi = n - 1;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (A[mid] == target) {
            return 1;
        } else if (A[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int temp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A, A + n);
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> temp;
        cout << find(temp) << '\n';
    }
}