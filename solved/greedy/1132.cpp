#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

long long arr[10];
bool non_zero[10];
string st[50];
int n;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> st[i];
}

void solve() {
    for (int i = 0; i < n; i++) {
        long long cur = 1;
        non_zero[st[i].front() - 'A'] = true;
        for (int j = st[i].size() - 1; j >= 0; j--) {
            arr[st[i][j] - 'A'] += cur;
            cur *= 10;
        }
    }
    int tmp;
    long long mn = 111111111111111;
    for (int i = 0; i < 10; i++) {
        if (non_zero[i])
            continue;
        if (mn <= arr[i])
            continue;
        tmp = i;
        mn = arr[i];
    }
    arr[tmp] = 0;
    sort(arr, arr + 10);
    long long sum = 0;
    for (int i = 0; i < 10; i++)
        sum += arr[i] * i;
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}