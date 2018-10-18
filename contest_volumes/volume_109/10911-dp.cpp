#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

uint16_t encode(string &state)
{
    uint16_t e = 0, b = 1;
    for (auto it = state.begin(); it != state.end(); it++, b <<= 1)
        if (*it == '1')
            e += b;
    return e;
}

int main()
{
    string pairs;
    unique_ptr<double[]> distances(new double[1 << (2 * 8)]);
    distances[0] = 0;
    for (int n, case_number = 1; cin >> n && n != 0; case_number++) {
        pair<int, int> points[2 * n];
        for (int i = 0; i < 2 * n; i++)
            cin >> pairs >> points[i].first >> points[i].second;

        fill(distances.get() + 1, distances.get() + (1 << (2 * n)), numeric_limits<double>::max());
        for (uint16_t i = 2; i <= 2 * n; i += 2) {
            pairs.assign(2 * n - i, '0');
            pairs.resize(2 * n, '1');
            do {
                const uint16_t e = encode(pairs);
                const uint16_t j = find(pairs.begin(), pairs.end(), '1') - pairs.begin();
                for (uint16_t k = j + 1; k < 2 * n; k++)
                    if (pairs[k] == '1') {
                        double d = sqrt(pow(points[j].first - points[k].first, 2) + pow(points[j].second - points[k].second, 2));
                        const uint16_t f = e - (1 << j) - (1 << k);
                        distances[e] = min(distances[e], distances[f] + d);
                    }
            } while (next_permutation(pairs.begin(), pairs.end()));
        }

        cout << "Case " << case_number << ": " << fixed << setprecision(2) << distances[(1 << (2 * n)) - 1] << endl;
    }
    return 0;
}
