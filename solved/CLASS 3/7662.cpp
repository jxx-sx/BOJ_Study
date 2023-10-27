#include <iostream>
#include <queue>
#include <vector>

using namespace std;

priority_queue<int> desc, asc_deprecated;
priority_queue<int, vector<int>, greater<int>> asc, desc_deprecated;
int n;

void pop(int x) {
    if (x > 0) {
        while (desc.size()) {
            if (asc_deprecated.empty() or desc.top() != asc_deprecated.top()) {
                desc_deprecated.push(desc.top());
                desc.pop();
                break;
            }
            asc_deprecated.pop();
            desc.pop();
        }
    } else {
        while (asc.size()) {
            if (desc_deprecated.empty() or asc.top() != desc_deprecated.top()) {
                asc_deprecated.push(asc.top());
                asc.pop();
                break;
            }
            desc_deprecated.pop();
            asc.pop();
        }
    }
}

void init() {
    cin >> n;
    while (desc.size())
        desc.pop();
    while (desc_deprecated.size())
        desc_deprecated.pop();
    while (asc.size())
        asc.pop();
    while (asc_deprecated.size())
        asc_deprecated.pop();
}

void solve() {
    char c;
    int num;
    while (n--) {
        cin >> c >> num;
        if (c == 'I') {
            desc.push(num);
            asc.push(num);
        } else
            pop(num);
    }

    vector<int> v;
    while (desc.size()) {
        while (desc.size()) {
            if (asc_deprecated.empty() or desc.top() != asc_deprecated.top()) {
                v.push_back(desc.top());
                desc.pop();
                continue;
            }
            asc_deprecated.pop();
            desc.pop();
        }
    }
    if (v.size())
        cout << v.front() << ' ' << v.back() << '\n';
    else
        cout << "EMPTY\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }
}