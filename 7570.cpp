#include <iostream>
#include <vector>

using namespace std;
vector<int> lis;
int n;
int arr[1000000];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    return;
}

void solve() {
    lis.push_back(arr[0]);
    for (int i = 1; i < n; i++) {
        if (lis.back() < arr[i]) {
            lis.push_back(arr[i]);
            continue;
        }
        *lower_bound(lis.begin(), lis.end(), arr[i]) = arr[i];
    }
    
    cout << n - lis.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}