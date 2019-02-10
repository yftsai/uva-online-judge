#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<uint32_t>> heights;
    for (uint16_t n, m; cin >> n >> m && n > 0; ) {
        heights.resize(n);
        for (auto &hs: heights) {
            hs.resize(m);
            for (auto &h: hs)
                cin >> h;
        }

        uint16_t q;
        uint32_t l, u;
        for (cin >> q; q > 0 && cin >> l >> u; --q) {
            uint16_t i = 0;
            for (; i < n && heights[i][m - 1u] < l; ++i)
                ;
            uint16_t side = 0;
            for (uint16_t j = m; i + side < n && j > 0; ++i) {
                for (; j > 1 && heights[i][j - 2u] >= l; --j)
                    ;
                for (; 0 < j && i + side < n && j - 1u + side < m && heights[i + side][j - 1u + side] <= u; ++side)
                    ;
            }
            cout << side << endl;
        }
        cout << "-" << endl;
    }

    return 0;
}
