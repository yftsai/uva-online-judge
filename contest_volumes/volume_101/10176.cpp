// #trivial
#include <iostream>
using namespace std;

int main()
{
    int v = 0;
    for (char c; cin >> c; ) {
        if (c == '#') {
            cout << ((v == 0) ? "YES" : "NO") << endl;
            v = 0;
        }
        else
            v = (v * 2 + (c - '0')) % 131071;
    }
    return 0;
}
