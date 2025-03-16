// #easy
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    string line;
    map<char, uint32_t> counts;

    for (uint32_t n, d; cin >> n >> d && n > 0; counts.clear()) {
        cin >> line;

        uint32_t i = 0, j = 0;
        do {
            for (; i + d + 1 > j; j++)
                counts[ line[j] ]++;

            char c = (--counts.end())->first;
            cout << c;

            d++;
            do {
                auto it = counts.find(line[i++]);
                --it->second;
                if (it->second == 0)
                    counts.erase(it);
                d--;
            } while (c != line[i - 1]);
        } while (d > 0 && i + d < n);

        if (d == 0)
            cout << (line.data() + i);
        cout << endl;
    }

    return 0;
}
