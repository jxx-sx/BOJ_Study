#include <iostream>

using namespace std;

int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    int *arr[n + 1];
    for (int i = 1; i < n + 1; i++) {
        arr[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++) {
            arr[i][j] = -1;
        }
        arr[i][i] = 0;
    }
    int s, e, t;
    for (int i = 0; i < m; i++) {
        cin >> s >> e >> t;
        if (arr[s][e] > t || arr[s][e] == -1)
            arr[s][e] = t;
    }

    for (int k = 1; k < n + 1; k++) {
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < n + 1; j++) {
                if (arr[i][k] == -1 || arr[k][j] == -1)
                    continue;
                int before = arr[i][j];
                int after = arr[i][k] + arr[k][j];
                if (before > after || before == -1)
                    arr[i][j] = after;
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (arr[i][j] == -1)
                arr[i][j] = 0;
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}