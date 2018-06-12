// #dynamic_programming #longest_increasing_subsequence
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    vector<int> tower_heights;
    int clen;           // 1) continuous towers including the last tower without any demolishment
    vector<int> heights;// 2) continuous towers prior to the last towers, which are demolished
                        //    mapping the length of the continuous towers to the height of the last one
    int dlen;           // 3) continuous towers including the last one but excluding demolished towers

    int z, n;
    for (cin >> z; z > 0 && cin >> n; z--) {
        tower_heights.resize(n);
        for (int i = 0; i < n; i++)
            cin >> tower_heights[i];

        clen = 0, heights.clear(), dlen = 0;
        int max_length = 0;
        for (size_t i = 0; i < tower_heights.size(); i++) {
            dlen = (dlen == 0 || tower_heights[i - 1] >= tower_heights[i]) ? 0 : (dlen + 1);

            auto it = lower_bound(heights.begin(), heights.end(), tower_heights[i]);
            if (it != heights.begin())
                dlen = max(dlen, (decltype(dlen))(it - heights.begin() + 1));

            if (clen > 0) {
                heights.resize(max(heights.size(), (size_t)clen), tower_heights[i - 1]);
                heights[clen - 1] = min(heights[clen - 1], tower_heights[i - 1]);
            }
            clen = (clen == 0 || tower_heights[i - 1] >= tower_heights[i]) ? 1 : (clen + 1);

            max_length = max(max_length, max(clen, dlen));
        }

        cout << max_length << endl;
    }

    return 0;
}
