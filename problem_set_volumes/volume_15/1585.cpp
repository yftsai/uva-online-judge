// #trivial
// There might be input issues that a Python implementation might not pass.
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    string result;
    for (cin >> n; n > 0 && cin >> result; n--) {
        int prev = 0, score = 0;
        for (char c: result)
            if (c == 'X')
                prev = 0;
            else {
                prev++;
                score += prev;
            }
        cout << score << endl;
    }

    return 0;
}
