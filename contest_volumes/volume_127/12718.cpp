// #easy
#include <iostream>
using namespace std;

int main()
{
    string line;

    uint16_t t;
    cin >> t;
    for (uint16_t cn = 1; cn <= t && cin >> line; cn++) {
        uint32_t count = 0;
        for (uint16_t i = 0; i < line.size(); i++) {
            bool is_odd[26] = { false };
            int16_t odd_count = 0;
            for (uint16_t j = i; j < line.size(); j++) {
                uint16_t k = line[j] - 'a';
                odd_count += (is_odd[k] = !is_odd[k]) ? 1 : -1;

                if (odd_count == 0 || odd_count == 1)
                    count++;
            }
        }
        cout << "Case " << cn << ": " << count << endl;
    }

    return 0;
}
