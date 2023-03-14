#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> lis, ans;
int arr[1000];
int n;
int ind[1000];

void make_lis() {
    ind[0] = 0;
    lis.push_back(arr[0]);

    for (int i = 1; i < n; i++) {
        if (lis.back() < arr[i]) {
            ind[i] = lis.size();
            lis.push_back(arr[i]);
            continue;
        }
        auto lb = lower_bound(lis.begin(), lis.end(), arr[i]);
        ind[i] = lb - lis.begin();
        *lb = arr[i];
    }
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    return;
}

void solve() {
    make_lis();
    int cur = lis.size() - 1;
    cout << lis.size() << '\n';
    for (int i = n - 1; i >= 0; i--) {
        if (ind[i] == cur) {
            ans.push_back(arr[i]);
            cur--;
            if (cur == -1)
                break;
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << ' ';
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}