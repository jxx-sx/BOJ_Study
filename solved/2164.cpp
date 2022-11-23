#include <iostream>

using namespace std;

int queue[1000001];
int n, start = 1, last;
void init() {
    last = n + 1;
    for (int i = 1; i <= n; i++)
        queue[i] = i;
}
void pop() { start += 1; }
void push() {
    queue[last] = queue[start];
    last += 1;
}
int size() { return last - start; }
int main() {
    cin >> n;
    init();
    while (size() != 1) {
        pop();
        if (size() == 1)
            break;
        push();
        pop();
    }
    cout << queue[start];
}