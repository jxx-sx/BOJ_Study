#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

pair<int, int> *arr;
int *ind;
int n;
vector<int> v;

void solve() {
    for (int i = 0; i < n; i++) {
        if (v.empty() || v.back() <= arr[i].second) {
            v.push_back(arr[i].second);
            ind[i] = v.size() - 1;
        } else {
            int tmp = upper_bound(v.begin(), v.end(), arr[i].second) - v.begin();
            v[tmp] = arr[i].second;
            ind[i] = tmp;
        }
    }

    vector<int> indV;
    int count = v.size() - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (ind[i] == count) {
            count -= 1;
        } else {
            indV.push_back(i);
        }
    }

    cout << indV.size();
}

void init() {
    cin >> n;
    arr = new pair<int, int>[n];
    ind = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }
    sort(arr, arr + n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}
