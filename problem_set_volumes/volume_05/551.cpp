// #parsing
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    const array<string, 5> obrackets = { "(*", "(", "[", "{", "<" };    // opening
    const array<string, 5> cbrackets = { "*)", ")", "]", "}", ">" };    // closing
    auto match = [](const array<string, 5> &brackets, const char *s) {
        return find_if(brackets.begin(), brackets.end(),
            [&](const string &b) { return equal(b.begin(), b.end(), s); });
    };

    string line;
    vector<uint16_t> brackets;

    while (getline(cin, line)) {
        bool valid = true;
        uint16_t pos = 0;

        brackets.clear();
        for (uint16_t i = 0; i < line.size() && valid; i++, pos++) {
            auto oit = match(obrackets, line.c_str() + i);
            auto cit = match(cbrackets, line.c_str() + i);

            if (oit != obrackets.end()) {
                i += oit->size() - 1;
                const uint16_t type = oit - obrackets.begin();
                brackets.push_back(type);
            }
            else if (cit != cbrackets.end()) {
                i += cit->size() - 1;
                const uint16_t type = cit - cbrackets.begin();
                if (!brackets.empty() && brackets.back() == type)
                    brackets.pop_back();
                else
                    valid = false;
            }
        }

        if (valid && brackets.empty())
            cout << "YES" << endl;
        else
            cout << "NO " << (pos + (valid ? 1 : 0)) << endl;
    }

    return 0;
}
