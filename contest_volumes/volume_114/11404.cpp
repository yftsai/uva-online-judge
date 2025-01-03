// #longest_common_sequence
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<pair<uint16_t, string>> row, row_n;
    string palindrome;
    uint32_t psize = 0;

    for (string line; cin >> line; ) {
        row.clear();
        row.resize(line.size());
        palindrome.clear();
        psize = 0;

        for (uint16_t i = 0, j = line.size() - 1; i < line.size(); i++, j--, row.swap(row_n)) {
            row_n.resize(line.size() - i + 1);
            for (uint16_t k = 1; k < row_n.size(); k++) {
                auto &cell = row_n[k];

                if (line[j] == line[k - 1]) {
                    cell.first = row[k - 1].first + 1;
                    cell.second = row[k - 1].second + line[j];
                }
                else {
                    const auto &left = row_n[k - 1], &above = row[k];
                    if (left.first > above.first
                        || (left.first == above.first && left.second < above.second))
                        cell = left;
                    else
                        cell = above;
                }
            }

            auto cell = &row_n.back();
            uint16_t size = cell->second.size();
            if (size > 0) {
                size = size * 2 - 1;
                if (size > psize || (size == psize && cell->second < palindrome)) {
                    palindrome.swap(cell->second);
                    psize = size;
                }
            }
            --cell;
            size = cell->second.size() * 2;
            if (size > psize || (size == psize && cell->second < palindrome)) {
                palindrome = cell->second;
                psize = size;
            }
        }
        cout << palindrome;
        if (psize % 2 > 0)
            palindrome.pop_back();
        reverse(palindrome.begin(), palindrome.end());
        cout << palindrome << endl;
    }

    return 0;
}
