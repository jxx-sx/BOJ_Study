#include <iostream>
#include <vector>

using namespace std;

vector<int> deque;

void push_front() {
    int temp;
    cin >> temp;
    deque.insert(deque.begin(), temp);
}

void push_back() {
    int temp;
    cin >> temp;
    deque.push_back(temp);
}

void pop_front() {
    if (deque.size()) {
        cout << deque.front() << endl;
        deque.erase(deque.begin());
        return;
    }
    cout << -1 << endl;
}

void pop_back() {
    if (deque.size()) {
        cout << deque.back() << endl;
        deque.pop_back();
        return;
    }
    cout << -1 << endl;
}

void size() { cout << deque.size() << endl; }

void empty() {
    if (deque.empty()) {
        cout << 1 << endl;
        return;
    }
    cout << 0 << endl;
}

void front() {
    if (deque.size()) {
        cout << deque.front() << endl;
        return;
    }
    cout << -1 << endl;
}

void back() {
    if (deque.size()) {
        cout << deque.back() << endl;
        return;
    }
    cout << -1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    string str;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str;
        if (str == "push_front")
            push_front();
        else if (str == "push_back")
            push_back();
        else if (str == "pop_front")
            pop_front();
        else if (str == "pop_back")
            pop_back();
        else if (str == "size")
            size();
        else if (str == "empty")
            empty();
        else if (str == "front")
            front();
        else if (str == "back")
            back();
    }
}