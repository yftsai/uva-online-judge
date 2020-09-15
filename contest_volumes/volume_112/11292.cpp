// #easy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> diameters(20000), heights(20000);
    for (uint16_t n, m; cin >> n >> m && n != 0; ) {
        diameters.resize(n);
        for (auto &d: diameters)
            cin >> d;
        heights.resize(m);
        for (auto &h: heights)
            cin >> h;

        sort(diameters.begin(), diameters.end());
        sort(heights.begin(), heights.end());

        int cost = 0;
        for (uint16_t i = 0, j = 0; i < n && cost >= 0; ++i) {
            while (j < m && heights[j] < diameters[i])
                ++j;
            if (j == m)
                cost = -1;
            else
                cost += heights[j++];
        }

        if (cost < 0)
            cout << "Loowater is doomed!" << endl;
        else
            cout << cost << endl;
    }

    return 0;
}
