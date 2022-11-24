#include <iostream>

using namespace std;

int n, ans = 0;
int *arr;

bool check(int length) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == arr[length]) {
            return false;
        }
        if (abs(arr[i] - arr[length]) == abs(length - i)) {
            return false;
        }
    }
    return true;
}

void dfs(int length) {
    if (n == length) {
        ans += 1;
        return;
    }
    for (int i = 0; i < n; i++) {
        arr[length] = i;
        if (check(length)) {
            dfs(length + 1);
        } else {
        }
    }
}

void init() {
    cin >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    dfs(0);
    cout << ans;
}