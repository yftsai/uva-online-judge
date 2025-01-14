// #trivial
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    for (string beds; cin >> beds; ) {
        uint32_t d = 0;
        uint32_t i = 0;
        for (; i < beds.size() && beds[i] == '.'; i++)
            ;
        d = i > 0 ? i - 1 : 0;

        for (uint32_t j = i + 1; j < beds.size(); j++)
            if (beds[j] == 'X') {
                if (i + 1 < j)
                    d = max<uint32_t>((j - i - 2) / 2, d);
                i = j;
            }

        if (i + 1u < beds.size())
            d = max<uint32_t>((beds.size() - i - 2), d);

        cout << d << endl;
    }

    return 0;
}
