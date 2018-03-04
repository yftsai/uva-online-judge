// #dynamic_programming
#include <iostream>
#include <deque>
using namespace std;

int count(const uint32_t *sums, uint32_t begin, uint32_t end)   { return sums[end - 1] - sums[begin - 1]; }
int compare(const uint32_t *sums, uint32_t lbegin, uint32_t lend, uint32_t rbegin, uint32_t rend)
{
    return count(sums, lbegin, lend) * (rend - rbegin) - count(sums, rbegin, rend) * (lend - lbegin);
}

int main()
{
    const uint32_t max_n = 100000;
    uint32_t prefix_sums[max_n + 1];    // the index starts from 1 as the problem description
    prefix_sums[0] = 0;

    uint32_t t, n, min_length;
    for (cin >> t; t > 0 && cin >> n >> min_length; t--) {
        uint32_t j = 1;
        for (char c; j <= min_length && cin >> c; j++)
            prefix_sums[j] = prefix_sums[j - 1] + c - '0';

        uint32_t max_begin = 1, max_end = j, i = 1;
        deque<int> indexes;
        for (char c; j <= n && cin >> c; i++, j++) {
            prefix_sums[j] = prefix_sums[j - 1] + c - '0';

            indexes.push_back(i);
            while (indexes.size() >= 2 && compare(prefix_sums, *next(indexes.rbegin()), i + 1, *indexes.rbegin(), i + 1) >= 0)
                indexes.pop_back();
            if (compare(prefix_sums, indexes.front(), i + 1, max_begin, max_end) <= 0)
                indexes.pop_front();

            while (indexes.size() >= 2 && compare(prefix_sums, indexes.front(), *next(indexes.begin()), indexes.front(), j + 1) <= 0)
                indexes.pop_front();
            if (indexes.size() == 1 && compare(prefix_sums, indexes.front(), i + 1, indexes.front(), j + 1) <= 0)
                indexes.pop_front();

            const uint32_t begin = (indexes.size() == 0) ? (i + 1) : indexes.front(), end = j + 1;
            int cmp = compare(prefix_sums, begin, end, max_begin, max_end);
            if (cmp > 0 || (cmp == 0 && end - begin < max_end - max_begin))
                max_begin = begin, max_end = j + 1;
        }

        cout << max_begin << " " << (max_end - 1) << endl;
    }
    return 0;
}
