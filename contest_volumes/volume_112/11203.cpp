// #easy
#include <iostream>
#include <string>
using namespace std;

uint16_t count(const char *&s)
{
    uint16_t count = 0;
    for (; *s == '?'; s++)
        count++;
    return count;
}

bool parse(const char *s, uint16_t &x, uint16_t &y, uint16_t &z)
{
    x = count(s);

    if (*s == 'M')
        s++;
    else
        return false;

    y = count(s);

    if (*s == 'E')
        s++;
    else
        return false;

    z = count(s);
    return *s == '\0';
}

int main()
{
    uint32_t n;
    string line;
    for (cin >> n; n > 0 && cin >> line; --n) {
        uint16_t x, y, z;
        if (!parse(line.c_str(), x, y, z) || x == 0 || y == 0 || x + y != z)
            cout << "no-theorem" << endl;
        else
            cout << "theorem" << endl;
    }

    return 0;
}
