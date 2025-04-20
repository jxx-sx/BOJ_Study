#include <iostream>
#include <vector>

using namespace std;

int TC;
int arr[500000];
int n;
long long ans;

vector<int> merge_sort(int s, int e) {
    if (s == e)
        return vector<int>(1, arr[s]);
    vector<int> l = merge_sort(s, (s + e) / 2);
    vector<int> r = merge_sort((s + e) / 2 + 1, e);
    vector<int> rtn;

    int l_i = 0, r_i = 0;
    while (l_i < l.size() and r_i < r.size()) {
        if (l[l_i] <= r[r_i]) {
            ans += rtn.size() - l_i;
            rtn.push_back(l[l_i++]);
        } else {
            rtn.push_back(r[r_i++]);
        }
    }

    while (l_i < l.size()) {
        ans += rtn.size() - l_i;
        rtn.push_back(l[l_i++]);
    }

    while (r_i < r.size()) {
        rtn.push_back(r[r_i++]);
    }

    return rtn;
}

void solve() {
    merge_sort(0, n - 1);
    cout << ans;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    ans = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    solve();
}