#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

// given unused railroads[start][i] = (departure_time, arrival_time, destination)
// returns (arrival_time, travel_time)
pair<int, int> schedule(vector<vector<tuple<int, int, int>>> &railroads, int arr_time, int city, int dest)
{
    pair<int, int> itinerary(numeric_limits<int>::max(), 0);

    if (city == dest)
        itinerary = make_pair(arr_time, 0);
    else
        while (railroads[city].size() > 0 && get<0>(railroads[city].back()) >= arr_time) {
            auto r = railroads[city].back();
            railroads[city].pop_back();
            pair<int, int> i = schedule(railroads, get<1>(r), get<2>(r), dest);
            itinerary = min(itinerary, make_pair(i.first, i.first - get<0>(r)));
        }

    return itinerary;
}

int main()
{
    int scenarios;
    cin >> scenarios;
    for (int s = 1; s<=scenarios; s++){
        int c, t;
        cin >> c;
        vector<string> cities(c);
        for (auto &city: cities)
            cin >> city;
        sort(cities.begin(), cities.end());
        auto get_city_index = [&cities](string &c) { return lower_bound(cities.begin(), cities.end(), c) - cities.begin(); };

        vector<vector<tuple<int, int, int>>> railroads(cities.size());
        for (cin >> t; t > 0; --t) {
            // assuming the stops sorted by time
            int nstops, arr_time, dest;
            string city;
            cin >> nstops >> arr_time >> city;
            dest = get_city_index(city);
            for (; nstops>1; --nstops) {
                int dep_time = arr_time, start = dest;
                cin >> arr_time >> city;
                railroads[start].push_back(make_tuple(dep_time, arr_time, dest = get_city_index(city)));
            }
        }

        int earliest_time;
        string start, dest;
        cin >> earliest_time >> start >> dest;

        for (auto &rs: railroads)
            sort(rs.begin(), rs.end());
        pair<int, int> itinerary = schedule(railroads, earliest_time, get_city_index(start), get_city_index(dest));

        cout << "Scenario " << s << endl;
        if (itinerary.first == numeric_limits<int>::max())
            cout << "No connection" << endl;
        else
            cout << "Departure "
                << setw(4) << setfill('0') << (itinerary.first - itinerary.second)
                << " " << start << endl
                << "Arrival   "
                << setw(4) << setfill('0') << itinerary.first
                << " " << dest << endl;
        cout << endl;
    }

    return 0;
}
