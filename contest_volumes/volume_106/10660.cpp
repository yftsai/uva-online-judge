#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;

constexpr uint16_t col_count = 5, rol_count = 5;
constexpr uint16_t area_count = col_count * rol_count;
constexpr uint16_t office_count = 5;

struct area
{
    int16_t row, col;
    uint16_t population;
    array<uint16_t, office_count> distances;
};

template<uint16_t I = 0>
void find_min_distance(
    vector<area> &areas,
    array<uint16_t, office_count> &offices,
    uint32_t &min_distance,
    array<uint16_t, office_count> &min_offices)
{
    for (offices[I] = (I == 0) ? 0 : (offices[I - 1] + 1); offices[I] < area_count; ++offices[I]) {
        const int16_t r = offices[I] / col_count;
        const int16_t c = offices[I] % col_count;
        for (area &a: areas)
            a.distances[I] = abs(a.row - r) + abs(a.col - c);
        find_min_distance<I + 1>(areas, offices, min_distance, min_offices);
    }
}

template<>
void find_min_distance<office_count>(
    vector<area> &areas,
    array<uint16_t, office_count> &offices,
    uint32_t &min_distance,
    array<uint16_t, office_count> &min_offices)
{
    uint32_t d = 0;
    for (const area &a: areas)
        d += *min_element(a.distances.begin(), a.distances.end()) * a.population;
    if (d < min_distance) {
        min_distance = d;
        min_offices = offices;
    }
}

int main()
{
    vector<area> areas;

    uint32_t t, n;
    for (cin >> t; t > 0; --t) {
        cin >> n;
        areas.resize(n);
        for (area &a: areas)
            cin >> a.row >> a.col >> a.population;

        uint32_t min_distance = numeric_limits<uint32_t>::max();
        array<uint16_t, office_count> offices, min_offices;
        find_min_distance(areas, offices, min_distance, min_offices);

        for (uint16_t i = 0; i < min_offices.size(); ++i)
            cout << ((i == 0) ? "" : " ") << min_offices[i];
        cout << endl;
    }

    return 0;
}
