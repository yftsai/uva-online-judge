// #trivial
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    string line;

    cout.precision(4);
    cout.setf(ios::fixed);

    getline(cin, line);
    uint32_t test_count = stoi(line);
    for (getline(cin, line); test_count > 0; --test_count) {
        map<string, uint32_t> counts;
        uint32_t count = 0;
        for (; getline(cin, line) && line.size() > 0; ++count) {
            auto it = counts.lower_bound(line);
            if (it == counts.end() || it->first != line)
                counts.emplace_hint(it, line, 1u);
            else
                ++it->second;
        }

        for (auto &p: counts)
            cout << p.first << " " << double(p.second) / count * 100 << endl;
        if (test_count > 1)
            cout << endl;
    }

    return 0;
}
