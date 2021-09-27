// #dynamic_programming
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void rank_substrings(
    const uint16_t size,
    vector<vector<uint16_t>> &ranks,
    vector<pair<pair<uint16_t, uint16_t>, uint16_t>> &local_ranks)
{
    if (ranks[size - 1].size() == 0) {
        const uint16_t seq_size = ranks[0].size();
        const uint16_t prefix_size = size / 2;
        const uint16_t suffix_size = size - prefix_size;
        rank_substrings(prefix_size, ranks, local_ranks);
        rank_substrings(suffix_size, ranks, local_ranks);

        for (uint16_t i = 0; i < seq_size; i++) {
            local_ranks[i].first.first = ranks[prefix_size - 1][i];
            local_ranks[i].first.second = ranks[suffix_size - 1][(i + prefix_size) % seq_size];
            local_ranks[i].second = i;
        }
        sort(local_ranks.begin(), local_ranks.end());

        auto &rs = ranks[size - 1];
        rs.resize(seq_size);
        for (uint16_t i = 0, r = 0; i < local_ranks.size(); i++) {
            if (0 < i && local_ranks[i - 1].first < local_ranks[i].first)
                r++;
            rs[local_ranks[i].second] = r;
        }
    }
}

int main()
{
    string seq;
    vector<vector<uint16_t>> ranks;
    vector<pair<pair<uint16_t, uint16_t>, uint16_t>> local_ranks;

    uint32_t t;
    for (cin >> t; t > 0 && cin >> seq; t--) {
        const uint16_t size = seq.size();
        if (ranks.size() < size)
            ranks.resize(size);
        for (uint16_t i = 0; i < size; i++)
            ranks[i].clear();

        ranks[0].resize(size);
        transform(seq.begin(), seq.end(), ranks[0].begin(),
            [](char c) { return c - 'A'; });
        local_ranks.resize(size);

        rank_substrings(size, ranks, local_ranks);

        const auto &r = ranks[size - 1];
        uint16_t min_index = min_element(r.begin(), r.end()) - r.begin();
        cout << seq.substr(min_index, size - min_index)
            << seq.substr(0, min_index) << endl;
    }

    return 0;
}
