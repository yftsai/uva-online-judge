// #binary_tree #easy
#include <iostream>
#include <string>
using namespace std;

uint16_t print_postord(const char *preord, const char *inord, char inord_end)
{
    if (*inord == inord_end)
        return 0;
    else if (*preord == *inord) {
        uint16_t n = print_postord(preord + 1, inord + 1, inord_end);
        cout << *preord;
        return n + 1;
    }
    else {
        uint16_t n = print_postord(preord + 1, inord, *preord);
        n += print_postord(preord + 1 + n, inord + n + 1, inord_end);
        cout << *preord;
        return 1 + n;
    }
}

int main()
{
    for (string preord, inord; cin >> preord >> inord; ) {
        print_postord(preord.c_str(), inord.c_str(), '\0');
        cout << endl;
    }
    return 0;
}
