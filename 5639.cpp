#include <iostream>
#include <vector>

using namespace std;


struct node {
    node *p;
    int data;
    node *l, *r;
};

node start;
vector<node> v;

void add(int x) {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int inp;
    cin >> inp;
    start.p = nullptr;
    start.l = nullptr;
    start.r = nullptr;
    start.data = inp;
    v.push_back(start);

    while (cin >> inp) {
        add(inp);
    }
}