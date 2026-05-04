// #suffix_array
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ranked_suffix_t
{
    uint16_t rank;
    uint16_t index;
    uint16_t aux_rank;
};

void double_prefix(const string &s, uint16_t plen, vector<ranked_suffix_t> &suffixes)
{
    sort(suffixes.begin(), suffixes.end(),
        [](const ranked_suffix_t &s, const ranked_suffix_t &t) {
            return s.index < t.index;
        });
    for (uint16_t i = 0; i < s.size(); i++)
        suffixes[i].aux_rank = i + plen < s.size() ? suffixes[i + plen].rank : 0;

    sort(suffixes.begin(), suffixes.end(),
        [](const ranked_suffix_t &s, const ranked_suffix_t &t) {
            if (s.rank != t.rank)
                return s.rank < t.rank;
            else
                return s.aux_rank < t.aux_rank;
        });

    for (uint16_t i = 0, j, r = 1; i < s.size(); i = j, r++) {
        const auto suffix = suffixes[i];
        const auto rank = suffix.rank;
        const auto aux_rank = suffix.aux_rank;
        for (j = i + 1; j < s.size() && rank == suffixes[j].rank && aux_rank == suffixes[j].aux_rank; j++)
            ;
        for (uint16_t k = i; k < j; k++)
            suffixes[k].rank = r;
    }
}

int main()
{
    vector<ranked_suffix_t> suffixes;
    vector<uint16_t> sa_idxs, lcps;
    vector<pair<uint16_t, uint16_t>> stack;
    vector<uint16_t> repetitions;

    for (string line; getline(cin, line) && line.size() > 0; ) {
        line.erase(remove(line.begin(), line.end(), ' '), line.end());

        uint16_t n = line.size();
        suffixes.resize(n);
        for (uint16_t i = 0; i < n; i++) {
            suffixes[i].rank = line[i] - 'A' + 1;   // reserve 0 for an empty string
            suffixes[i].index = i;
        }

        for (uint16_t sz = 1; sz < n; sz *= 2)
            double_prefix(line, sz, suffixes);

        sa_idxs.resize(n);
        for (uint16_t si = 0; si < n; si++)
            sa_idxs[ suffixes[si].index ] = si;

        lcps.resize(n);
        for (uint16_t i = 0, len = 0; i < n; i++) {
            uint16_t si = sa_idxs[i];
            if (si + 1 == n) {
                lcps[si] = 0;
                len = 0;
            }
            else {
                uint16_t j = suffixes[si + 1].index;
                while (i + len < n && j + len < n && line[i + len] == line[j + len])
                    len++;
                lcps[si] = len;
                if (len > 0) len--;
            }
        }

        stack.clear();
        repetitions.clear();
        for (uint16_t i = 0; i < n; i++) {
            while (stack.size() > 0 && stack.back().second > lcps[i]) {
                auto begin = stack.back().first;
                auto len = stack.back().second;
                stack.pop_back();
                if (len - 1u >= repetitions.size())
                    repetitions.resize(len, 0);
                repetitions[len - 1] = max<uint16_t>(i + 1 - begin, repetitions[len - 1]);

                len--;
                if (len > 0 && (stack.size() == 0 || stack.back().second < len))
                    stack.emplace_back(begin, len);
            }

            if (lcps[i] > 0 && (stack.size() == 0 || stack.back().second < lcps[i]))
                stack.emplace_back(i, lcps[i]);
        }

        for (auto r: repetitions)
            cout << r << endl;
        cout << endl;
    }

    return 0;
}
