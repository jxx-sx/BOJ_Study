#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long base_x, base_y;

struct Point {
    long long x, y;
    bool operator<(const Point &t) const { return y == t.y ? x < t.x : y < t.y; }
} base;

inline long long ccw(Point a, Point b, Point c) { return a.x * b.y + b.x * c.y + c.x * a.y - a.x * c.y - b.x * a.y - c.x * b.y; }

inline long long dist(Point t) { return (base.x - t.x) * (base.x - t.x) + (base.y - t.y) * (base.y - t.y); }

bool comp(Point a, Point b) {
    auto tmp = ccw(base, a, b);
    return tmp == 0 ? (dist(a) < dist(b)) : tmp > 0;
}

int n;
vector<Point> v, st;

void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a.x >> a.y;
}

void solve() {
    sort(v.begin(), v.end());
    base = v[0];
    sort(v.begin() + 1, v.end(), comp);
    st.push_back(v[0]);
    st.push_back(v[1]);
    for (int i = 2; i < n; i++) {
        while (st.size() > 1) {
            auto tmp = st.back();
            st.pop_back();
            if (ccw(st.back(), tmp, v[i]) > 0) {
                st.push_back(tmp);
                break;
            }
        }
        st.push_back(v[i]);
    }
    cout << st.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}