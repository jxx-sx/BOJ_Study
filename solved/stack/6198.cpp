#include <iostream>
#include <stack>

using namespace std;

stack<int> st;
int n, arr[80000];
long long ans;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < n; i++) {
        while (st.size() and arr[st.top()] <= arr[i]) {
            ans += i - st.top() - 1;
            st.pop();
        }
        st.push(i);
    }
    while (st.size()) {
        ans += n - st.top() - 1;
        st.pop();
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}