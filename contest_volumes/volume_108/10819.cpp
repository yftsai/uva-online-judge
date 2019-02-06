// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    const uint32_t invalid_favour_value = 1 << 30;
    vector<uint32_t> favour_values(10000 + 1 + 200);
    for (uint32_t m, n; cin >> m >> n; ) {
        const uint32_t max_m = (m + 200 > 2000) ? (m + 200) : m;
        uint32_t max_fv = 0;
        favour_values.assign(1, 0);
        for (uint32_t i = 0, p, f; i < n && cin >> p >> f; ++i) {
            favour_values.resize(min(uint32_t(favour_values.size()) + p, max_m + 1), invalid_favour_value);
            for (uint32_t j = (favour_values.size() > p) ? (favour_values.size() - p) : 0; j > 0; --j)
                if (favour_values[j - 1u] != invalid_favour_value) {
                    uint32_t &fv = favour_values[j - 1u + p];
                    fv = max((fv == invalid_favour_value) ? 0 : fv, favour_values[j - 1u] + f);
                    max_fv = max(max_fv, (j - 1u + p <= m || j - 1u + p > 2000) ? fv : max_fv);
                }
        }
        cout << max_fv << endl;
    }
    return 0;
}
