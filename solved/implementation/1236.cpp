#include <iostream>

using namespace std;

int main() {
    int n, m, ansN = 0, ansM = 0;
    int *nn, *mm;
    char ch;
    cin >> n >> m;
    nn = new int[n]{0};
    mm = new int[m]{0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> ch;
            if (ch == 'X') {
                nn[i] = 1;
                mm[j] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (nn[i] == 0)
            ansN += 1;
    }
    for (int i = 0; i < m; i++) {
        if (mm[i] == 0)
            ansM += 1;
    }
    int answer = (ansN > ansM) ? ansN : ansM;

    cout << answer;
}