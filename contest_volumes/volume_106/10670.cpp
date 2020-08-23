// #greedy
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    uint32_t case_count;
    uint16_t agency_count;
    string line;
    vector<pair<uint32_t, string>> agencies(100);    // cost, name

    cin >> case_count;
    for (uint32_t case_number = 1, m, n;
         case_number <= case_count && cin >> n >> m >> agency_count;
         ++case_number) {

        agencies.resize(agency_count);

        for (uint16_t i = 0; i < agency_count && cin >> line; ++i) {
            auto p = line.find(':');
            auto q = line.find(',', p);
            agencies[i].second = line.substr(0, p);
            const uint16_t a = stoi(line.substr(p + 1, q));
            const uint16_t b = stoi(line.substr(q + 1));

            agencies[i].first = 0;
            for (uint32_t j = n; j != m; )
                if (j / 2 < m || (j - j / 2) * a < b) {
                    const uint32_t k = max(j / 2, m);
                    agencies[i].first += (j - k) * a;
                    j = k;
                }
                else {
                    agencies[i].first += b;
                    j /= 2;
                }
        }

        cout << "Case " << case_number << endl;
        sort(agencies.begin(), agencies.end());
        for (const auto agency: agencies)
            cout << agency.second << " " << agency.first << endl;
    }

    return 0;
}
