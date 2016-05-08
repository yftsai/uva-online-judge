#include <iostream>
#include <string>
using namespace std;

char get_value(istream &is, string &s, size_t &pos, char len)
{
    char v = 0;
    for (char i=0; i<len; ++i, ++pos) {
        if (pos >= s.size())
            getline(cin, s), pos = 0;
        v = v*2 + s[pos] - '0';
    }
    return v;
}

char decode(const string &h, char ks, char kv)
{
    size_t index = 0;
    for (char i=1; i<ks; ++i)
        index += (1 << i) - 1;
    return h[index + kv];
}

int main()
{
    for (string header; getline(cin, header); ) {
        string message;
        size_t pos = 0;

        for (char ks, kv; (ks = get_value(cin, message, pos, 3)) != 0; )
            while ((kv = get_value(cin, message, pos, ks)) != (1 << ks) - 1)
                cout << decode(header, ks, kv);
        cout << endl;
    }

    return 0;
}
