// #spanning_tree
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

stringstream ss(string &line)
{
    getline(cin, line);
    return stringstream(line);
}

struct road
{
    uint32_t speed;
    uint16_t ends[2];
    bool operator<(const road &r) const { return speed < r.speed; }
};

uint16_t get_group(vector<uint16_t> &groups, uint16_t i)
{
    uint16_t g = groups[i];
    for (; groups[g] != g; g = groups[g])
        ;
    for (uint16_t k = groups[i]; k != g; k = groups[i = k])
        groups[i] = g;
    return g;
}

int main()
{
    vector<road> roads;
    vector<uint16_t> groups;

    for (string line; getline(cin, line); ) {
        uint16_t n, m;
        stringstream(line) >> n >> m;

        roads.clear();
        for (road r; ss(line) >> r.ends[0] >> r.ends[1] >> r.speed; ) {
            r.ends[0]--;
            r.ends[1]--;
            roads.push_back(r);
        }
        sort(roads.begin(), roads.end());

        uint16_t senergy, eenergy;
        stringstream(line) >> senergy >> eenergy;

        uint16_t k;
        ss(line) >> k;

        groups.resize(n);
        for (uint16_t src, dst; k > 0 && ss(line) >> src >> dst; k--) {
            src--;
            dst--;

            uint32_t min_energy = roads.back().speed - roads.front().speed;
            for (uint16_t i = 0; i < roads.size(); i++) {
                iota(groups.begin(), groups.end(), 0);
                for (uint16_t j = i; j < roads.size() && roads[j].speed - roads[i].speed < min_energy ; j++) {
                    uint16_t g = get_group(groups, roads[j].ends[0]);
                    uint16_t h = get_group(groups, roads[j].ends[1]);
                    if (g != h)
                        groups[g] = h;
                    if (get_group(groups, src) == get_group(groups, dst))
                        min_energy = roads[j].speed - roads[i].speed;
                }
            }

            cout << senergy + eenergy + min_energy << endl;
        }
    }

    return 0;
}
