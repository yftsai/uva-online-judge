// #backtracking
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
using namespace std;

bool form_square(
    const vector<uint16_t> &lengths,
    vector<bool> is_used,
    array<vector<uint16_t>, 4> &edges,
    const uint32_t square_edge_length,
    uint16_t e = 0,
    uint32_t edge_length = 0)
{
    if (e >= edges.size())
        return true;
    else {
        uint16_t begin = (edges[e].size() == 0)
            ? ((e == 0) ? lengths.size() : edges[e - 1].front())
            : edges[e].back();
        while (begin > 0 && is_used[begin - 1])
            begin--;
        const uint16_t end = (edges[e].size() == 0 && begin > 0) ? (begin - 1) : 0;

        for (uint16_t i = begin, last_length = 0; i > end; i--)
            if (!is_used[i - 1]
                && lengths[i - 1] != last_length
                && edge_length + lengths[i - 1] <= square_edge_length) {
                last_length = lengths[i - 1];

                is_used[i - 1] = true;
                edges[e].push_back(i - 1);
                edge_length += lengths[i - 1];

                if (form_square(lengths, is_used, edges, square_edge_length, e, edge_length))
                    return true;

                if (edge_length == square_edge_length
                    && form_square(lengths, is_used, edges, edge_length, e + 1))
                    return true;

                edge_length -= lengths[i - 1];
                edges[e].pop_back();
                is_used[i - 1] = false;
            }

        return false;
    }
}

int main()
{
    vector<uint16_t> lengths(20);
    vector<bool> is_used(20, false);
    array<vector<uint16_t>, 4> edges;
    uint32_t n;
    uint16_t m;

    for (cin >> n; n > 0 && cin >> m; --n) {
        lengths.resize(m);
        for (auto &length: lengths)
            cin >> length;
        sort(lengths.begin(), lengths.end());
        is_used.assign(m, false);

        for (auto &edge: edges)
            edge.clear();
        const auto sum = accumulate(lengths.begin(), lengths.end(), 0);
        const bool can_be_square = (sum % 4 == 0) && form_square(lengths, is_used, edges, sum / 4);
        cout << (can_be_square ? "yes" : "no") << endl;
    }

    return 0;
}
