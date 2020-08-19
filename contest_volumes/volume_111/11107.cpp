// #suffix_array
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct substring
{
    uint16_t seq_idx, pos;
    bool operator<(const substring &) const { return false; }
};

void unflatten(
    const uint16_t n,
    const vector<pair<uint16_t, substring>> &ranked_strs,
    vector<bool> &is_substring,
    vector<vector<substring>> &substrs,
    vector<vector<uint32_t>> *ranks = nullptr)
{
    const uint16_t min_size = n / 2 + 1;

    for (auto bit = ranked_strs.begin(), eit = ranked_strs.begin(); bit != ranked_strs.end(); bit = eit) {
        is_substring.assign(n, false);
        uint16_t count = 0;
        for (eit = bit; eit != ranked_strs.end() && eit->first == bit->first; ++eit)
            if (!is_substring[eit->second.seq_idx]) {
                is_substring[eit->second.seq_idx] = true;
                ++count;
            }
        if (count >= min_size) {
            substrs.emplace_back();
            for (auto it = bit; it != eit; ++it) {
                substrs.back().push_back(it->second);
                if (ranks != nullptr) {
                    (*ranks)[it->second.seq_idx][it->second.pos] = substrs.size();
                }
            }
        }
    }
}

int main()
{
    vector<string> sequences(100);
    vector<vector<vector<uint32_t>>> ranks;                 // ranks[e][i][pos] of prefixes of length 2^e
    vector<pair<uint16_t, substring>> ranked_strs;
    vector<vector<substring>> substrs, extended_substrs;
    vector<bool> is_substring;
    const uint32_t NO_RANK = 0;

    bool is_first = true;
    for (uint16_t n; (cin >> n) && n != 0; is_first = false) {
        sequences.resize(n);
        for (string &s: sequences)
            cin >> s;

        // rank the substrings of length 1
        ranks.resize(1);
        ranks.back().resize(n);
        ranked_strs.clear();
        for (uint16_t i = 0; i < n; ++i) {
            ranks[0][i].assign(sequences[i].size(), NO_RANK);
            for (uint16_t pos = 0; pos < sequences[i].size(); ++pos)
                ranked_strs.emplace_back(sequences[i][pos], substring{i, pos});
        }

        substrs.clear();
        sort(ranked_strs.begin(), ranked_strs.end());
        unflatten(n, ranked_strs, is_substring, substrs, &ranks.back());

        // double prefixes
        uint16_t length_exponent = 0;
        for (; ; ++length_exponent) {
            const uint16_t length = (1 << length_exponent);
            ranks.emplace_back();
            ranks.back().resize(n);
            for (uint16_t i = 0; i < n; ++i)
                if (sequences[i].size() >= length * 2)
                    ranks.back()[i].assign(sequences[i].size() - length * 2 + 1, NO_RANK);

            extended_substrs.clear();
            for (const auto &positions: substrs) {
                ranked_strs.clear();
                for (const auto &p: positions)
                    if (p.pos + length * 2u <= sequences[p.seq_idx].size() &&
                        ranks[length_exponent][p.seq_idx][p.pos + length] != NO_RANK)
                        ranked_strs.emplace_back(ranks[length_exponent][p.seq_idx][p.pos + length], p);

                sort(ranked_strs.begin(), ranked_strs.end());
                unflatten(n, ranked_strs, is_substring, extended_substrs, &ranks.back());
            }

            if (extended_substrs.size() > 0)
                substrs.swap(extended_substrs);
            else
                break;
        }

        // concatenate the longest common substrings
        uint16_t length = (substrs.size() == 0) ? 0 : (1 << length_exponent);
        for (uint16_t len = length / 2, e = length_exponent - 1; len > 0; len /= 2, --e) {
            extended_substrs.clear();
            for (const auto &positions: substrs) {
                ranked_strs.clear();
                for (const auto &p: positions)
                    if (uint16_t(p.pos + length + len) <= sequences[p.seq_idx].size() &&
                        ranks[e][p.seq_idx][p.pos + length] != NO_RANK)
                        ranked_strs.emplace_back(ranks[e][p.seq_idx][p.pos + length], p);

                sort(ranked_strs.begin(), ranked_strs.end());
                unflatten(n, ranked_strs, is_substring, extended_substrs);
            }

            if (extended_substrs.size() > 0) {
                substrs.swap(extended_substrs);
                length += len;
            }
        }

        if (!is_first)
            cout << endl;
        if (length == 0)
            cout << "?" << endl;
        else
            for (const auto &s: substrs)
                cout << sequences[s.front().seq_idx].substr(s.front().pos, length) << endl;
    }

    return 0;
}
