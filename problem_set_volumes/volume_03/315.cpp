// #articulation_point #depth_first_search
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
using namespace std;

struct place
{
    uint16_t index;
    uint16_t min_reachable_index;
    bool is_critical;
};

int main()
{
    vector<set<uint16_t>> neighbors;
    vector<place> places;
    vector<pair<uint16_t, set<uint16_t>::iterator>> stack;

    uint16_t n;
    for (string line; getline(cin, line) && (n = stoul(line)) > 0; stack.clear()) {
        neighbors.assign(n, set<uint16_t>());
        for (uint16_t u; getline(cin, line); ) {
            stringstream ss(line);
            if (ss >> u && u == 0)
                break;
            else
                for (uint16_t v; ss >> v; ) {
                    neighbors[u - 1u].insert(v - 1u);
                    neighbors[v - 1u].insert(u - 1u);
                }
        }

        uint16_t critical_point_count = 0;
        uint16_t indexed_count = 0, root_child_count = 0;
        places.assign(n, place{n, n, false});
        stack.emplace_back(0, neighbors[0].begin());
        while (stack.size() > 0) {
            uint16_t p = stack.back().first;
            auto &it = stack.back().second;

            if (places[p].index == n)
                places[p].index = places[p].min_reachable_index = (indexed_count++);
            else {
                places[p].min_reachable_index = min(places[p].min_reachable_index, places[*it].min_reachable_index);
                if (places[p].index <= places[*it].min_reachable_index)
                    places[p].is_critical = true;
            }

            for (; it != neighbors[p].end() && places[*it].index != n; ++it)
                if (stack.size() > 1u && *it != stack[stack.size() - 2u].first)
                    places[p].min_reachable_index = min(places[p].min_reachable_index, places[*it].index);

            if (it == neighbors[p].end()) {
                if (p == 0)
                    places[p].is_critical = (root_child_count >= 2u);
                if (places[p].is_critical)
                    critical_point_count++;
                stack.pop_back();
            }
            else {
                if (p == 0)
                    root_child_count++;
                stack.emplace_back(*it, neighbors[*it].begin());
            }
        }
        cout << critical_point_count << endl;
    }

    return 0;
}
