// #dynamic_programming
#include <iostream>
#include <map>
using namespace std;

uint32_t count(const uint32_t n, const uint16_t k)
{
    typedef pair<uint16_t, uint16_t> remainders;    // remainder, remaider of the sum of its digits
    map<remainders, uint32_t> counts;

    uint16_t ndigit = 1;
    uint32_t base = 1;
    while (n / base >= 10)
        base *= 10, ndigit++;

    // starting from the most significant digits
    for (uint16_t i = 1; i < n / base; i++)
        counts[remainders(i % k, i % k)]++;

    uint16_t digit_sum = n / base;
    for (base /= 10, ndigit--; base > 0; base /= 10, ndigit--) {
        decltype(counts) next_counts;

        // starting new prefixes
        for (uint16_t i = 1; i <= 9; i++)
            next_counts[remainders(i % k, i % k)]++;

        // extending known prefixes
        for (const auto &remainder_count: counts) {
            const auto &rs = remainder_count.first;
            const auto &count = remainder_count.second;
            if (rs.second == 0 || rs.second + ndigit * 9 >= k)
                for (uint16_t i = 0; i <= 9; i++)
                    next_counts[remainders((rs.first * 10u + i) % k, (rs.second + i) % k)] += count;
        }

        // starting prefixes with only the least significant digit smaller than the upper bound
        const uint16_t digit = (n / base) % 10;
        for (uint16_t i = 0; i < digit; i++)
            next_counts[remainders((n / base - digit + i) % k, (digit_sum + i) % k)]++;
        digit_sum += digit;

        counts.swap(next_counts);
    }
    counts[remainders(n % k, digit_sum % k)]++;

    return counts[remainders(0, 0)];
}

int main()
{
    uint16_t t, k;
    uint32_t a, b;
    for (cin >> t; t > 0 && cin >> a >> b >> k; t--)
        cout << (count(b, k) - ((a == 1) ? 0 : count(a - 1, k))) << endl;

    return 0;
}
