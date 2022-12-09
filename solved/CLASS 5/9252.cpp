#include <iostream>
#include <stack>
#include <string>

using namespace std;
string a, b;
void solve() {
    stack<char> st;
    int arr[a.size() + 1][b.size() + 1];
    for (int i = 0; i <= a.size(); i++)
        for (int j = 0; j <= b.size(); j++)
            arr[i][j] = 0;
    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            if (a[i - 1] == b[j - 1])
                arr[i][j] = arr[i - 1][j - 1] + 1;
            else
                arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
        }
    }
    int x = a.size();
    int y = b.size();

    while (x > 0 and y > 0) {
        if (arr[x - 1][y] == arr[x][y])
            x--;
        else if (arr[x][y - 1] == arr[x][y])
            y--;
        else if (arr[x - 1][y - 1] < arr[x][y]) {
            st.push(a[x - 1]);
            x--;
            y--;
        }
        if (st.size() == arr[a.size()][b.size()]) {
            break;
        }
    }

    cout << arr[a.size()][b.size()] << '\n';
    while (!st.empty()) {
        cout << st.top();
        st.pop();
    }
}
void init() {
    cin >> a >> b;
    solve();
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
}