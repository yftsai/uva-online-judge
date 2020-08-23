// #shortest_path
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main()
{
    string ns[2];
    vector<vector<uint16_t>> distances;

    for (uint32_t p, r, case_number = 1; cin >> p >> r && p != 0; ++case_number) {
        distances.resize(p);
        for (auto &ds: distances)
            ds.assign(p, p);

        map<string, uint16_t> names;
        for (uint32_t i = 0; i < r && cin >> ns[0] >> ns[1]; ++i) {
            uint32_t indexes[2];
            for (uint16_t j = 0; j < 2; ++j) {
                auto it = names.lower_bound(ns[j]);
                if (it == names.end() || it->first != ns[j])
                    it = names.emplace_hint(it, ns[j], names.size());
                indexes[j] = it->second;
            }
            distances[ indexes[0] ][ indexes[1] ] = distances[ indexes[1] ][ indexes[0] ] = 1;
        }

        for (uint16_t m = 0; m < p; ++m)
            for (uint16_t src = 0; src < p; ++src)
                for (uint16_t dst = 0; dst < p; ++dst)
                    distances[src][dst] = min<uint16_t>(distances[src][m] + distances[m][dst],
                                                        distances[src][dst]);

        uint16_t max_degree = 0;
        for (uint16_t i = 0; i < p; ++i)
            for (uint16_t j = i + 1; j < p; ++j)
                max_degree = max(distances[i][j], max_degree);


        cout << "Network " << case_number << ": ";
        if (max_degree < p)
            cout << max_degree << endl;
        else
            cout << "DISCONNECTED" << endl;
        cout << endl;
    }

    return 0;
}
