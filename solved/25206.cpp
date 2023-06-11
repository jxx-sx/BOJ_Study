#include <iostream>
#include <map>
#include <string>

using namespace std;
double a, b;
map<string, double> m = {{"A+", 4.5}, {"A0", 4.0}, {"B+", 3.5}, {"B0", 3.0}, {"C+", 2.5}, {"C0", 2.0}, {"D+", 1.5}, {"D0", 1.0}, {"F", 0}};

void init() {
    double c;
    string name, grade;
    while (cin >> name >> c >> grade) {
        if (grade != "P") {
            b += c;
            a += c * m.find(grade)->second;
        }
    }
}

void solve() {
    cout << fixed;
    cout.precision(6);
    cout << a / b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}