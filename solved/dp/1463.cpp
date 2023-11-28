#include <iostream>

using namespace std;

int ans[1000001];

int main() {
    int temp;
    cin >> temp;
    ans[1] = 0;
    for (int i = 2; i <= temp; i++) {
        if (i % 3 == 0 && i % 2 == 0) {
            ans[i] = min({ans[i / 3] + 1, ans[i / 2] + 1, ans[i - 1] + 1});
        } else if (i % 3 == 0) {
            ans[i] = min(ans[i / 3] + 1, ans[i - 1] + 1);
        } else if (i % 2 == 0) {
            ans[i] = min(ans[i / 2] + 1, ans[i - 1] + 1);
        } else {
            ans[i] = ans[i - 1] + 1;
        }
    }
    cout << ans[temp];
}