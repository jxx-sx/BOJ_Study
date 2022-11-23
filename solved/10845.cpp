#include <iostream>
#include <vector>

using namespace std;

vector<int> queue;

void push() {
    int num;
    cin >> num;
    queue.push_back(num);
}

void pop() {
    if (queue.size() == 0) {
        cout << -1 << endl;
        return;
    }
    int temp = queue.front();
    queue.erase(queue.begin());
    cout << temp << endl;
}

void size() { cout << queue.size() << endl; }

void empty() {
    if (queue.size())
        cout << 0 << endl;
    else
        cout << 1 << endl;
}

void front() {
    if (queue.size())
        cout << queue.front() << endl;

    else
        cout << -1 << endl;
}

void back() {
    if (queue.size())
        cout << queue.back() << endl;
    else
        cout << -1 << endl;
}

int main() {
    string str;
    int temp;
    cin >> temp;
    for (int i = 0; i < temp; i++) {
        cin >> str;
        if (str == "push")
            push();
        if (str == "pop")
            pop();
        if (str == "size")
            size();
        if (str == "empty")
            empty();
        if (str == "front")
            front();
        if (str == "back")
            back();
    }
}