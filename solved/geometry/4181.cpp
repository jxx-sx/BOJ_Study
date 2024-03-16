#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long x_0, y_0;

inline long long dist(long long x, long long y) { return x * x + y * y; }

struct point {
    long long x, y;

    bool operator<(const point &t) const {
        long long ret = (x - x_0) * (t.y - y_0) - (t.x - x_0) * (y - y_0);
        if (!ret)
            return dist(x - x_0, y - y_0) < dist(t.x - x_0, t.y - y_0);
        return ret > 0;
    }
};

bool ccw(point p1, point p2, point p3) {
    int s = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
    s -= (p1.y * p2.x + p2.y * p3.x + p3.y * p1.x);
    return s == 0;
}

int n;
vector<point> v, rev;

void init() {
    point tmp;
    char ch;
    cin >> n;
    while (n--) {
        cin >> tmp.x >> tmp.y >> ch;
        if (ch == 'Y') {
            v.push_back(tmp);
            if (v[0].x > tmp.x or (v[0].x == tmp.x and v[0].y > tmp.y))
                swap(v[0], v.back());
        }
    }
    x_0 = v[0].x;
    y_0 = v[0].y;
}

void solve() {
    sort(v.begin(), v.end());
    cout << v.size() << '\n';
    rev.push_back(v.back());
    v.pop_back();
    while (ccw(v[0], rev[0], v.back())) {
        rev.push_back(v.back());
        v.pop_back();
    }

    for (auto a : v)
        cout << a.x << ' ' << a.y << '\n';
    for (auto a : rev)
        cout << a.x << ' ' << a.y << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}
