#include <ctime>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    cout << t->tm_year + 1900 << "-";
    cout.width(2);
    cout.fill('0');
    cout << t->tm_mon + 1 << "-";
    cout.width(2);
    cout.fill('0');
    cout << t->tm_mday;
}