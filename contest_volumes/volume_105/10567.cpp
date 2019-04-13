// #easy #binary_search
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

static uint16_t to_state_id(char c)
{
    if ('A' <= c && c <= 'Z')
        return c - 'A';
    else
        return c - 'a' + 26;
}

int main()
{
    string sequence;

    cin >> sequence;
    vector<uint32_t> serial_numbers[52];
    for (uint32_t sn = 0; sn < sequence.size(); ++sn)
        serial_numbers[to_state_id(sequence[sn])].push_back(sn);

    uint16_t q;
    for (cin >> q; q > 0 && cin >> sequence; --q) {
        uint32_t end_index = 0;
        for (char c: sequence) {
            const auto &sns = serial_numbers[to_state_id(c)];
            auto it = lower_bound(sns.begin(), sns.end(), end_index);
            if (it != sns.end())
                end_index = *it + 1;
            else {
                end_index = 0;
                break;
            }
        }

        if (end_index == 0)
            cout << "Not matched" << endl;
        else
            cout << "Matched " << serial_numbers[to_state_id(sequence[0])].front()
                 << " " << (end_index - 1u) << endl;
    }

    return 0;
}
