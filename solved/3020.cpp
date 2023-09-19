#include <algorithm>
#include <iostream>

using namespace std;

int n, h, cur, last, cnt, m; // cur: 현재 장애물 갯수, last 마지막 갱신, cnt 정답 개수, m 최소값
vector<pair<int, int>> v;

void init() {
    int tmp;
    cin >> n >> h;
    cur = n / 2;
    m = n;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(i % 2 ? make_pair(tmp, -1) : make_pair(h - tmp, 1));
    }
    sort(v.begin(), v.end());
}

void solve() {
    int i = 0;
    while (true) {
        if (i >= v.size()) {
            if (cur < m) {
                m = cur;
                cnt = h - last;
            } else if (cur == m)
                cnt += h - last;
            break;
        }
        if (v[i].first == last) {
            cur += v[i].second;
            i++;
            continue;
        }
        if (cur < m) {
            m = cur;
            cnt = v[i].first - last;
        } else if (cur == m)
            cnt += v[i].first - last;
        last = last = v[i].first;
    }
    cout << m << ' ' << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}