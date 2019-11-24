// #chinese_postman_problem #route_inspection_problem
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

constexpr uint32_t invalid_length = numeric_limits<uint32_t>::max();

void minimize_match_length(
    const vector<uint16_t> &vertices,
    const vector<vector<uint32_t>> &distances,
    const uint16_t index_mask,
    vector<uint32_t> &match_lengths)
{
    if (match_lengths[index_mask] == invalid_length) {
        uint16_t i = 0;
        for (; i < vertices.size() && ((index_mask >> i) & 1) == 0; ++i)
            ;
        const uint16_t v = vertices[i];

        for (uint16_t j = i + 1; j < vertices.size(); ++j)
            if ((index_mask >> j) & 1) {
                const uint32_t subset_mask = index_mask ^ (1u << i) ^ (1u << j);
                minimize_match_length(vertices, distances, subset_mask, match_lengths);
                const uint16_t w = vertices[j];
                const uint32_t d = distances[v][w];
                match_lengths[index_mask] = min(match_lengths[index_mask], d + match_lengths[subset_mask]);
            }
    }
}

int main()
{
    vector<bool> is_odd_degrees;
    vector<vector<uint32_t>> distances;
    vector<uint16_t> vertices;
    vector<uint32_t> match_lengths;

    for (uint16_t n, m; cin >> n >> m; ) {
        is_odd_degrees.assign(n, false);
        distances.resize(n);
        for (auto &ds: distances)
            ds.assign(n, invalid_length);

        uint32_t length = 0, len;
        for (uint16_t i = 0, v, w; i < m && cin >> v >> w >> len; ++i) {
            is_odd_degrees[v - 1] = !is_odd_degrees[v - 1];
            is_odd_degrees[w - 1] = !is_odd_degrees[w - 1];
            distances[v - 1][w - 1] = distances[w - 1][v - 1] = min(distances[v - 1][w - 1], len);
            length += len;
        }

        for (uint16_t k = 0; k < n; ++k)
            for (uint16_t i = 0; i < n; ++i)
                for (uint16_t j = 0; distances[i][k] != invalid_length && j < n; ++j)
                    if (distances[k][j] != invalid_length)
                        distances[i][j] = distances[j][i] =
                            min(distances[i][j], distances[i][k] + distances[k][j]);

        vertices.clear();
        for (uint16_t i = 0; i < n; ++i)
            if (is_odd_degrees[i])
                vertices.push_back(i);
        match_lengths.assign(1u << vertices.size(), invalid_length);
        match_lengths[0] = 0;
        const uint16_t all_mask = (1u << vertices.size()) - 1;
        minimize_match_length(vertices, distances, all_mask, match_lengths);

        cout << (length + match_lengths[all_mask]) << endl;
    }

    return 0;
}
