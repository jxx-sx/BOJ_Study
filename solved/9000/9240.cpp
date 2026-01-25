#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Point {
    long long x, y; 
    bool operator<(const Point &t) const { return y == t.y ? x < t.x : y < t.y; }
    Point() : x(0), y(0) {}
};

inline long long dist(Point a) { return a.x * a.x + a.y * a.y; }

inline long long dist(Point a, Point b) {
    auto x = a.x - b.x;
    auto y = a.y - b.y;
    return x * x + y * y;
}

bool ccw(Point a, Point b, Point c) { return a.x * b.y + b.x * c.y + c.x * a.y - a.x * c.y - b.x * a.y - c.x * b.y > 0; }

bool comp(Point a, Point b) { return a.x * b.y == b.x * a.y ? dist(a) < dist(b) : a.x * b.y > b.x * a.y; }

int n;
vector<Point> v, st;

void init() {
    v.clear();
    st.clear();
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a.x >> a.y;
}

void solve() {
    sort(v.begin(), v.end());
    for (int i = 1; i < n; i++) {
        v[i].x -= v[0].x;
        v[i].y -= v[0].y;
    }
    sort(v.begin() + 1, v.end(), comp);
    st.resize(2);
    st[1] = v[1];
    for (int i = 2; i < n; i++) {
        while (st.size() > 1) {
            auto tmp = st.back();
            st.pop_back();
            if (ccw(st.back(), tmp, v[i])) {
                st.push_back(tmp);
                break;
            }
        }
        st.push_back(v[i]);
    }

    long long ans = 0;
    Point a, b;

    for (int i = 0; i < st.size(); i++) {
        for (int j = i + 1; j < st.size(); j++) {
            auto tmp = dist(st[i], st[j]);
            if (ans < tmp) {
                ans = tmp;
                a = st[i];
                b = st[j];
            }
        }
    }
    a.x += v[0].x;
    a.y += v[0].y;
    b.x += v[0].x;
    b.y += v[0].y;

    cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << '\n';
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

    return 0;
}