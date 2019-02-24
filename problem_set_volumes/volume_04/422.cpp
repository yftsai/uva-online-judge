// #string_search
#include <iostream>
#include <vector>
using namespace std;

pair<uint16_t, uint16_t> search(const vector<string> &puzzle,
                                uint16_t row,
                                uint16_t col,
                                const string &word,
                                const vector<uint16_t> &eq_lengths,
                                const pair<int16_t, int16_t> step)
{
    pair<int16_t, int16_t> pos(row, col);
    auto is_in_puzzle = [&] {
        return 0 <= pos.first && pos.first < int16_t(puzzle.size())
            && 0 <= pos.second && pos.second < int16_t(puzzle[pos.first].size());
    };
    auto advance = [&] { pos.first += step.first; pos.second += step.second; };

    uint16_t length = 0;
    for (; is_in_puzzle() && length < word.size(); advance()) {
        for (; length > 0 && word[length] != puzzle[pos.first][pos.second]; length = eq_lengths[length - 1u])
            ;
        if (word[length] == puzzle[pos.first][pos.second])
            ++length;
    }
    if (length == word.size()) {
        pos.first -= step.first * word.size();
        pos.second -= step.second * word.size();
    }

    return pos;
}

int main()
{
    uint16_t n;
    cin >> n;
    vector<string> puzzle(n);
    for (string &row: puzzle)
        cin >> row;

    vector<uint16_t> eq_lengths(1, 0);
    for (string word; cin >> word && word != "0"; ) {
        eq_lengths.resize(word.size());
        for (uint16_t i = 1; i < eq_lengths.size(); ++i) {
            uint16_t length = eq_lengths[i - 1u];
            for (; length > 0 && word[length] != word[i]; length = eq_lengths[length - 1u])
                ;
            eq_lengths[i] = (word[length] == word[i]) ? (length + 1u) : 0;
        }

        pair<int16_t, int16_t> pos(n, n), step;
        auto is_found = [&] {
            return 0 <= pos.first && pos.first < n
                && 0 <= pos.second && pos.second < n;
        };
        if (word.size() <= n) {
            for (uint16_t row = 0; row < n && !is_found(); ++row) {
                const pair<int16_t, int16_t> forward_steps[] = {
                    {0,  1},
                    {-1, 1},
                    {1,  1}
                };
                for (auto &s: forward_steps)
                    if (!is_found())
                        pos = search(puzzle, row, 0, word, eq_lengths, step = s);

                const pair<int16_t, int16_t> backward_steps[] = {
                    {0,  -1},
                    {-1, -1},
                    {1,  -1}
                };
                for (auto &s: backward_steps)
                    if (!is_found())
                        pos = search(puzzle, row, n - 1u, word, eq_lengths, step = s);
            }

            for (uint16_t col = 0; col < n && !is_found(); ++col) {
                const pair<int16_t, int16_t> forward_steps[] = {
                    {1,  0},
                    {1, -1},
                    {1,  1}
                };
                for (auto &s: forward_steps)
                    if (!is_found())
                        pos = search(puzzle, 0, col, word, eq_lengths, step = s);

                const pair<int16_t, int16_t> backward_steps[] = {
                    {-1, -1},
                    {-1,  1}
                };
                for (auto &s: backward_steps)
                    if (!is_found())
                        pos = search(puzzle, n - 1u, col, word, eq_lengths, step = s);
            }
        }

        if (is_found())
            cout << (pos.first + 1u) << "," << (pos.second + 1u)
                 << " " << (pos.first + 1u + step.first * (word.size() - 1u))
                 << "," << (pos.second + 1u + step.second * (word.size() - 1u)) << endl;
        else
            cout << "Not found" << endl;
    }

    return 0;
}
