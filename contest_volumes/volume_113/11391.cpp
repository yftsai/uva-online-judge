// #dynamic_programming
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

constexpr uint32_t unknown = numeric_limits<uint32_t>::max();

uint16_t get_position_mask(uint16_t col_count, uint16_t i, uint16_t j)
{
    return 1u << (col_count * i + j);
}

void count(const uint16_t r, const uint16_t c, const uint16_t board, vector<uint32_t> *counts)
{
    static const int16_t ds[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    if ((*counts)[board] == unknown) {
        (*counts)[board] = 0;
        for (int16_t i = 0, mask = 1; i < r && mask <= board; ++i)
            for (int16_t j = 0; j < c; ++j, mask <<= 1)
                if ((board & mask) != 0)
                    for (auto &d: ds) {
                        const pair<uint16_t, uint16_t> m(i + d[0] * 2, j + d[1] * 2);
                        if (0 <= m.first && m.first < r && 0 <= m.second && m.second < c) {
                            const uint16_t m_mask = get_position_mask(c, m.first, m.second);
                            const uint16_t n_mask = get_position_mask(c, i + d[0], j + d[1]);
                            if ((board & n_mask) != 0 && (board & m_mask) == 0) {
                                const uint16_t next_board = (board & ~mask & ~n_mask) | m_mask;
                                count(r, c, next_board, counts);
                                (*counts)[board] += (*counts)[next_board];
                            }
                        }
                    }
    }
}

int main()
{
    vector<vector<vector<uint32_t>>> counts(4);
    for (uint16_t r = 1; r <= 4; ++r) {
        counts[r - 1].resize(r);
        for (uint16_t c = 1; c <= r; ++c) {
            const uint32_t board_count = 1u << (r * c);
            counts[r - 1][c - 1].resize(board_count, unknown);
            counts[r - 1][c - 1][0] = 0;
            for (uint32_t board = 1; board < board_count; board <<= 1)
                counts[r - 1][c - 1][board] = 1;
        }
    }

    uint32_t t;
    uint16_t r, c, n;
    cin >> t;
    for (uint32_t case_number = 1; case_number <= t && cin >> r >> c >> n; ++case_number) {
        const bool is_transpose = (r < c);
        if (is_transpose)
            swap(r, c);

        uint16_t board = 0;
        for (uint16_t i = 0, x, y; i < n && cin >> x >> y; ++i)
            if (!is_transpose)
                board |= get_position_mask(c, x - 1, y - 1);
            else
                board |= get_position_mask(c, y - 1, x - 1);

        count(r, c, board, &counts[r - 1][c - 1]);
        cout << "Case " << case_number << ": " << counts[r - 1][c - 1][board] << endl;
    }

    return 0;
}
