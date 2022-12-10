#include <iostream>
#include <queue>

using namespace std;

int n;
int arr[3][3];
int tmp[3][3];
int inp[3];
priority_queue<int> pq;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    cin >> arr[0][0] >> arr[0][1] >> arr[0][2];
    arr[2][0] = arr[1][0] = arr[0][0];
    arr[2][1] = arr[1][1] = arr[0][1];
    arr[2][2] = arr[1][2] = arr[0][2];
    cin >> inp[0] >> inp[1] >> inp[2];

    tmp[2][2] = tmp[1][1] = tmp[0][0] = 2001;

    tmp[1][0] = arr[1][1] + inp[0];
    tmp[2][0] = arr[2][2] + inp[0];

    tmp[0][1] = arr[0][0] + inp[1];
    tmp[2][1] = arr[2][2] + inp[1];

    tmp[0][2] = arr[0][0] + inp[2];
    tmp[1][2] = arr[1][1] + inp[2];

    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++)
            arr[j][k] = tmp[j][k];
    }

    for (int i = 2; i < n; i++) {
        cin >> inp[0] >> inp[1] >> inp[2];
        if (i == n - 1) {
            tmp[0][0] = min(arr[0][1] + inp[2], arr[0][2] + inp[1]);
            tmp[1][0] = min(arr[1][0] + inp[2], arr[1][2] + inp[0]);
            tmp[2][0] = min(arr[2][0] + inp[1], arr[2][1] + inp[0]);
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++)
                    arr[j][k] = tmp[j][0];
            }
        }
        for (int j = 0; j < 3; j++) {
            tmp[j][0] = min(arr[j][1], arr[j][2]) + inp[0];
            tmp[j][1] = min(arr[j][0], arr[j][2]) + inp[1];
            tmp[j][2] = min(arr[j][1], arr[j][0]) + inp[2];
        }
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++)
                arr[j][k] = tmp[j][k];
        }
    }

    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            pq.push(-arr[j][k]);
        }
    }
    cout << -pq.top();
}