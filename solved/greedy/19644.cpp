#include <iostream>
#include <queue>

using namespace std;

long long l, ml, mk, ammo;
long long arr[3000001];
queue<long long> q;

void init() {
    cin >> l >> ml >> mk >> ammo;
    for (int i = 1; i <= l; i++)
        cin >> arr[i];
}

void solve() {
    long long cur = 0;
    for (int i = 1; i <= l; i++) {
        if (q.size() and q.front() == i) {
            cur -= mk;
            q.pop();
        }
        if (cur + mk >= arr[i]) {
            cur += mk;
            q.push(i + ml);
        } else if (ammo > 0) {
            ammo--;
        } else {
            cout << "NO";
            return;
        }
    }

    cout << "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}