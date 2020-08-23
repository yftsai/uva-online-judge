// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    uint16_t t, n;
    vector<uint32_t> values;

    for (cin >> t; t > 0 && cin >> n; --t) {
        values.resize(1, 0);

        for (uint16_t i = 0, p, w; i < n && cin >> p >> w; ++i) {
            values.resize(min<uint16_t>(values.size() + w, 31), 0);
            for (uint16_t j = values.size() - 1; j >= w; --j)
                values[j] = max(values[j - w] + p, values[j]);
        }

        for (uint16_t i = 1; i < values.size(); ++i)
            values[i] = max(values[i - 1], values[i]);

        uint16_t g;
        cin >> g;
        uint32_t max_value = 0;
        for (uint16_t i = 0, w; i < g && cin >> w; ++i)
            max_value += values[min<uint16_t>(w, values.size() - 1)];
        cout << max_value << endl;
    }

    return 0;
}
