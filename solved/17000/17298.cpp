#include <iostream>
#include <stack>

using namespace std;
int arr[1000000];
int ans[1000000];
int n;
stack<int> st;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    return;
}

void solve() {
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty()) {
            if (st.top() <= arr[i])
                st.pop();
            else
                break;
        }

        if (st.empty())
            ans[i] = -1;
        else
            ans[i] = st.top();
        st.push(arr[i]);
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}