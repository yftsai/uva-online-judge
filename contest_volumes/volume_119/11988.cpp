// #easy
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    for (string line, head, tail; getline(cin, line); head.clear(), tail.clear()) {
        for (string::const_iterator b = line.cbegin(), e; b != line.end(); b = (e == line.end()) ? e : next(e)) {
            e = find_if(b, line.cend(), [](const char c) { return c == '[' || c == ']'; });
            if (b != line.begin() && *prev(b) == '[') {
                auto it = head.insert(head.end(), b, e);
                reverse(it, head.end());
            }
            else
                tail.append(b, e);
        }
        reverse(head.begin(), head.end());
        cout << head << tail << endl;
    }
    return 0;
}
