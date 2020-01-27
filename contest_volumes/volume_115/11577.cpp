// #trivial
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string line;
    getline(cin, line);
    for (int n = stoi(line); n > 0 && getline(cin, line); --n) {
        uint32_t counts[26] = { 0 };
        for (const char c: line)
            if (isalpha(c))
                ++counts[tolower(c) - 'a'];
        line = "a";

        for (uint16_t i = 1, j = 0; i < 26; ++i)
            if (counts[i] == counts[j])
                line.push_back('a' + i);
            else if (counts[i] > counts[j])
                line.assign(1, 'a' + (j = i));

        cout << line << endl;
    }

    return 0;
}
