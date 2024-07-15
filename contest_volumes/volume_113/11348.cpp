// #easy
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    unordered_map<uint16_t, uint8_t> owners;
    cout.setf(ios::fixed);
    cout.precision(6);

    uint16_t k, n, m, type;
    cin >> k;
    for (uint16_t t = 1; t <= k; t++) {
        owners.clear();
        cin >> n;
        for (uint16_t owner = 0; owner < n; owner++)
            for (cin >> m; m > 0 && cin >> type; m--) {
                auto it = owners.emplace(type, owner).first;
                if (it->second != owner)
                    it->second = n;
            }

        uint16_t unique_counts[n] = { 0 };
        uint16_t unique_count = 0;
        for (const auto &p: owners)
            if (p.second < n) {
                unique_counts[p.second]++;
                unique_count++;
            }

        cout << "Case " << t << ":";
        for (auto c: unique_counts)
            cout << " " << ((unique_count == 0) ? 0.0 : (100.0 * c / unique_count)) << '%';
        cout << endl;
    }

    return 0;
}
