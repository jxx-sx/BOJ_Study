#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b;
    cin >> a >> b;
    bool arr[b + 1];
    for (int i = 0; i < b + 1; i++) {
        arr[i] = false;
    }
    vector<int> ans;

    for (int i = 2; i <= b; i++) {
        if (!arr[i]) {
            ans.push_back(i);
            int tmp = i;
            while (tmp <= b) {
                arr[tmp] = true;
                tmp += i;
            }
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] >= a) {
            cout << ans[i] << '\n';
        }
    }
}