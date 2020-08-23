// #dynamic_programming
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main()
{
    uint32_t n, x;
    vector<int16_t> windstrengths[10];
    vector<vector<uint32_t>> fuels(2);
    const uint32_t max_fuel = numeric_limits<uint32_t>::max();
    fuels[1].resize(9);

    for (cin >> n; n > 0 && cin >> x; --n) {
        for (int16_t i = 9; i >= 0; --i) {
            windstrengths[i].resize(x / 100);
            for (auto &w: windstrengths[i])
                cin >> w;
        }

        fuels[0].assign(9, max_fuel);
        fuels[0][0] = 0;
        for (uint16_t y = 0; y < uint16_t(x / 100); ++y, fuels[0].swap(fuels[1])) {
            for (uint16_t a = 0; a < 9; ++a) {
                fuels[1][a] = max_fuel;
                if (a > 0 && fuels[0][a - 1] < max_fuel)
                    fuels[1][a] = fuels[0][a - 1] + 60 - windstrengths[a - 1][y];
                if (fuels[0][a] < max_fuel)
                    fuels[1][a] = min(fuels[0][a] + 30 - windstrengths[a][y], fuels[1][a]);
                if (a + 1 < 9 && fuels[0][a + 1] < max_fuel)
                    fuels[1][a] = min(fuels[0][a + 1] + 20 - windstrengths[a + 1][y], fuels[1][a]);
            }
        }

        cout << fuels[0][0] << endl;
        cout << endl;
    }

    return 0;
}
