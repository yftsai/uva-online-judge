// #easy
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool arrange(vector<pair<int, int>> &pieces, uint16_t end, uint16_t index)
{
    bool is_solvable = false;
    if (index == end)
        is_solvable = (pieces[index - 1u].second == pieces[end].first);
    else {
        for (uint32_t i = index; i < pieces.size() && !is_solvable; ++i)
            if (i != end && pieces[index - 1u].second == pieces[i].first) {
                swap(pieces[index], pieces[i]);
                is_solvable = arrange(pieces, end, index + 1u);
                swap(pieces[index], pieces[i]);
            }
            else if (i != end && pieces[index - 1u].second == pieces[i].second) {
                swap(pieces[i].first, pieces[i].second);
                swap(pieces[index], pieces[i]);
                is_solvable = arrange(pieces, end, index + 1u);
                swap(pieces[index], pieces[i]);
            }
    }
    return is_solvable;
}

int main()
{
    vector<pair<int, int>> pieces;
    for (uint16_t n; cin >> n && n != 0; ) {
        uint16_t m;
        cin >> m;

        pieces.resize(m + 2u);
        cin >> pieces[0].first >> pieces[0].second
            >> pieces[n + 1u].first >> pieces[n + 1u].second;

        for (uint16_t i = 1; i < m + 2u; ++i)
            if (i != n + 1u)
                cin >> pieces[i].first >> pieces[i].second;

        cout << (arrange(pieces, n + 1u, 1u) ? "YES" : "NO") << endl;
    }

    return 0;
}
