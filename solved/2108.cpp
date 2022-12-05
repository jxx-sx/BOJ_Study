#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long double a = 0.0;
    int n, tmp;
    cin >> n;
    vector<int> v;
    int arr[8001];
    for (int i = 0; i < 8001; i++) {
        arr[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
        a += tmp / (double)n;
        arr[tmp + 4000] += 1;
    }
    int c;
    vector<int> vv;
    for (int i = 0; i < 8001; i++) {
        if (arr[i] > c) {
            vv.clear();
            vv.push_back(i - 4000);
            c = arr[i];
        } else if (arr[i] == c) {
            vv.push_back(i - 4000);
        }
    }
    sort(v.begin(), v.end());
    sort(vv.begin(), vv.end(), greater<int>());

    a = round(a);
    if (abs(a) == 0) {
        a = 0.0;
    }
    if (vv.size() != 1)
        vv.pop_back();
    cout << a << '\n';
    cout << v[n / 2] << '\n';
    cout << vv.back() << '\n';
    cout << v.back() - v.front();
}