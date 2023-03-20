#include <iostream>
#include <queue>

using namespace std;

int arr[5000000];
int n, l;
priority_queue<int, vector<int>, greater<int>> pq, will_delete;

void init() {
    int inp;
    cin >> n >> l;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return;
}

void solve() {
    for (int i = 0; i < n; i++) {
        pq.push(arr[i]);
        if (i >= l)
            will_delete.push(arr[i - l]);

        while (!will_delete.empty()) {
            if (pq.top() == will_delete.top()) {
                pq.pop();
                will_delete.pop();
            } else
                break;
        }
        cout << pq.top() << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}