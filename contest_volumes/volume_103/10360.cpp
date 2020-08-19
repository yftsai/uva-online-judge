// #matrix_sum
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<uint32_t>> fields(1025);

    uint32_t input_count;
    int16_t d;
    uint16_t n;
    for (cin >> input_count; input_count > 0 && cin >> d >> n; --input_count) {
        for (auto &row: fields)
            row.assign(1025, 0);

        int16_t max_x = 0, max_y = 0;
        for (uint16_t i = 0, x, y, size; i < n && cin >> x >> y >> size; ++i) {
            max_x = max<uint16_t>(x, max_x);
            max_y = max<uint16_t>(y, max_y);
            fields[x][y] = size;
        }

        uint32_t max_sum = fields[0][0];
        pair<int16_t, int16_t> location(0, 0);
        for (int16_t x = 0; x < int16_t(max_x + 1); ++x) {
            for (int16_t y = 0; y < int16_t(max_y + 1); ++y) {
                if (x > 0)
                    fields[x][y] += fields[x - 1][y];
                if (x > 0 && y > 0)
                    fields[x][y] -= fields[x - 1][y - 1];
                if (y > 0)
                    fields[x][y] += fields[x][y - 1];

                uint32_t sum = fields[x][y];
                pair<int16_t, int16_t> lb(x - 2 * d, y - 2 * d);
                if (lb.first > 0)
                    sum -= fields[lb.first - 1][y];
                if (lb.first > 0 && lb.second > 0)
                    sum += fields[lb.first - 1][lb.second - 1];
                if (lb.second > 0)
                    sum -= fields[x][lb.second - 1];

                if (sum > max_sum) {
                    max_sum = sum;
                    location.first = max(x - d, 0);
                    location.second = max(y - d, 0);
                }
            }
        }

        cout << location.first << " " << location.second << " " << max_sum << endl;
    }

    return 0;
}
