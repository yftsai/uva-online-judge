// #dynamic_programming
// The judge input may be ill-formatted that I cannot pass with Python.
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    for (int scenario_number = 1, n, r; cin >> n >> r && n > 0; scenario_number++) {
        vector<pair<int, int>> edges[n];
        for (int c1, c2, p; r > 0 && cin >> c1 >> c2 >> p; r--) {
            edges[c1 - 1].push_back(make_pair(c2 - 1, p));
            edges[c2 - 1].push_back(make_pair(c1 - 1, p));
        }
        int s, d, t;
        cin >> s >> d >> t;

        int tourist_counts[n] = { 0 };
        tourist_counts[s - 1] = t + 1;
        vector<int> cities(n);
        for (int i = 0; i < n; i++)
            cities[i] = i;
        for (; cities.size() > 0; cities.pop_back()) {
            for (size_t i = 0; i < cities.size(); i++)
                if (tourist_counts[ cities[i] ] > tourist_counts[ cities.back() ])
                    swap(cities[i], cities.back());
            for (const auto &p: edges[ cities.back() ])
                tourist_counts[p.first] = max(tourist_counts[p.first], min(p.second, tourist_counts[cities.back()]));
        }

        cout << "Scenario #" << scenario_number << endl;
        int tc = tourist_counts[d - 1] - 1;
        cout << "Minimum Number of Trips = " << ((t % tc == 0) ? (t / tc) : (t / tc + 1)) << endl;
        cout << endl;
    }
    return 0;
}
