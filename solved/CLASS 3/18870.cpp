#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int a[n];
    vector<int> v;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 0; i < n; i++) {
        cout << lower_bound(v.begin(), v.end(), a[i]) - v.begin() << ' ';
    }
}