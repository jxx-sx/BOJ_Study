#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int max = 0;
    int before;
    int inp, n;
    cin >> n;
    cin >> before;
    max = before;
    for (int i = 1; i < n; i++) {
        cin >> inp;
        before = (before + inp > inp ? before + inp : inp);
        max = (before > max ? before : max);
    }
    cout << max;
}