// #longest_increasing_subsequence
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> sequence;
    vector<int> last_values;
    vector<uint16_t> inc_lengths;

    for (uint16_t n; cin >> n; ) {
        sequence.resize(n);
        for (auto &v: sequence)
            cin >> v;

        last_values.clear();
        inc_lengths.clear();
        for (const auto &v: sequence) {
            auto it = lower_bound(last_values.begin(), last_values.end(), v);
            inc_lengths.push_back(it - last_values.begin());

            if (it == last_values.end())
                last_values.push_back(v);
            else
                *it = v;
        }

        uint16_t max_length = 0;
        last_values.clear();
        for (uint16_t i = sequence.size(); i > 0; --i) {
            auto it = lower_bound(last_values.begin(), last_values.end(), sequence[i - 1]);
            const uint16_t dec_length = it - last_values.begin();
            const uint16_t wavio_length = min(inc_lengths[i - 1], dec_length) * 2 + 1;
            max_length = max<uint16_t>(max_length, wavio_length);

            if (it == last_values.end())
                last_values.push_back(sequence[i - 1]);
            else
                *it = sequence[i - 1];
        }

        cout << max_length << endl;
    }

    return 0;
}
