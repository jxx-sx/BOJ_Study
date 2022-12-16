#include <iostream>

using namespace std;
int n, m, b;
int arr[500][500];
void solve(int l, int h) {
    int ans = 100000000;
    int ground;
    for (int i = l; i <= h; i++) {
        int time = 0;
        int tmp = b;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (arr[j][k] < i) {
                    b -= i - arr[j][k];
                    time += i - arr[j][k];
                } else {
                    b += arr[j][k] - i;
                    time += 2 * (arr[j][k] - i);
                }
            }
        }
        if (tmp >= 0 and ans >= time) {
            ans = time;
            ground = i;
        }
    }
    cout << ans << ' ' << ground;
}

void init() {
    int l = 256;
    int h = 0;
    cin >> n >> m >> b;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            h = max(h, arr[i][j]);
            l = min(l, arr[i][j]);
        }
    }
    solve(l, h);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}