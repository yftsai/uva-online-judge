// #graph #erdos_gallai_theorem
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<uint32_t> degrees(1000);
    vector<uint32_t> prefix_sums(1000);

    for (uint16_t n; cin >> n && n != 0; ) {
        degrees.resize(n);
        for (auto &d: degrees)
            cin >> d;
        sort(degrees.begin(), degrees.end());

        prefix_sums.resize(n);
        prefix_sums[0] = degrees[0];
        for (uint16_t i = 1; i < n; ++i)
            prefix_sums[i] = prefix_sums[i - 1] + degrees[i];

        bool is_valid = true;
        for (uint16_t i = 0, j = n; j > 0; --j) {
            const uint16_t k = n - j + 1;
            for (; i < j - 1 && degrees[i] < k; ++i)
                ;
            i = min<uint16_t>(i, j - 1);
            const uint32_t low_degree_sum = (i == 0) ? 0 : prefix_sums[i - 1];

            const uint32_t high_degree_sum = prefix_sums.back() - ((j == 1) ? 0 : prefix_sums[j - 2]);
            is_valid = is_valid && (high_degree_sum <= k * (k - 1) + low_degree_sum + k * (j - 1 - i));
        }

        if (prefix_sums.back() % 2 == 0 && is_valid)
            cout << "Possible" << endl;
        else
            cout << "Not possible" << endl;
    }

    return 0;
}
