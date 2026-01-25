#include <iostream>
#include <string>

using namespace std;

int n, m, answer = 100;
char set1[2][8] = {{'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B'}, {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W'}};
char **inp;

void solve() {
    int temp;
    for (int i = 0; i < n - 7; i++) {
        for (int j = 0; j < m - 7; j++) {
            temp = 0;
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 8; l++) {
                    if (set1[k % 2][l] != inp[i + k][j + l])
                        temp += 1;
                }
            }
            answer = (temp < answer ? temp : answer);

            temp = 0;
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 8; l++) {
                    if (set1[(k + 1) % 2][l] != inp[i + k][j + l])
                        temp += 1;
                }
            }
            answer = (temp < answer ? temp : answer);
        }
    }
}

void init() {
    char tmp;
    cin >> n >> m;
    inp = new char *[n];
    for (int i = 0; i < n; i++) {
        inp[i] = new char[m];
        for (int j = 0; j < m; j++) {
            cin >> inp[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    cout << answer;
}