// prime_factorization
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    constexpr uint32_t max_n = 10000001;
    constexpr uint32_t max_prime_value = sqrt(max_n);

    vector<int32_t> counts(2703670, 0);
    for (uint32_t n = 2; n < counts.size(); ++n) {
        if (counts[n] == 0) {
            counts[n] = 1;
            if (n <= max_prime_value)
                for (uint32_t m = n * n; m < counts.size(); m += n)
                    counts[m] = n;
        }
        else
            counts[n] = counts[n / counts[n]] + 1;
    }
    for (uint32_t n = 1; n < counts.size(); ++n)
        counts[n] += counts[n - 1];

    for (int32_t case_number = 1, n; cin >> n && n >= 0; ++case_number) {
        cout << "Case " << case_number << ": ";
        auto it = lower_bound(counts.begin(), counts.end(), n);
        if (it != counts.end() && *it == n)
            cout << (it - counts.begin()) << "!" << endl;
        else
            cout << "Not possible." << endl;
    }

    return 0;
}
