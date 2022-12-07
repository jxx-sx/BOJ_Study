#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long Min[3], Max[3];
    Min[0] = Min[1] = Min[2] = Max[0] = Max[1] = Max[2] = 0;
    long long tmp[3];
    int l, m, r;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l >> m >> r;
        tmp[0] = l + min(Min[0], Min[1]);
        tmp[1] = m + min(Min[0], min(Min[1], Min[2]));
        tmp[2] = r + min(Min[1], Min[2]);
        for (int j = 0; j < 3; j++) {
            Min[j] = tmp[j];
        }
        tmp[0] = l + max(Max[0], Max[1]);
        tmp[1] = m + max(Max[0], max(Max[1], Max[2]));
        tmp[2] = r + max(Max[1], Max[2]);
        for (int j = 0; j < 3; j++) {
            Max[j] = tmp[j];
        }
    }

    cout << max(Max[0], max(Max[1], Max[2])) << ' ' << min(Min[0], min(Min[1], Min[2]));
}