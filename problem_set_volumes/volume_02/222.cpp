// #dynamic_programming
#include <iostream>
#include <map>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    constexpr double eps = 0.0000001;
    int case_number = 0;
    cout << fixed << setprecision(2);
    for (double distance; cin >> distance && distance > 0; ) {
        double capacity, mpg, cost;
        int station_count;
        cin >> capacity >> mpg >> cost >> station_count;

        map<double, double> states;     // gas -> cost
        states[capacity] = cost;
        double position = 0, price = 0;
        for (double next_pos, next_p; station_count >= 0; station_count--, position = next_pos, price = next_p) {
            if (station_count > 0)
                cin >> next_pos >> next_p;
            else
                next_pos = distance;
            const double min_gas = (next_pos - position) / mpg;
            map<double, double> ss;
            auto update = [&ss] (double g, double c) {
                if (ss.find(g) == ss.end())
                    ss[g] = c;
                else
                    ss[g] = min(ss[g], c);
            };
            for (const auto &p: states) {
                if (p.first >= min_gas - eps)
                    update(max(p.first - min_gas, 0.0), p.second);
                double c = p.second + round((capacity - p.first) * price) / 100 + 2;
                if (p.first < min_gas - eps || p.first <= capacity / 2 + eps)
                    update(capacity - min_gas, c);
            }
            states.swap(ss);
        }

        cost = states.begin()->second;
        for (auto &p: states)
            cost = min(cost, p.second);
        cout << "Data Set #" << ++case_number << endl;
        cout << "minimum cost = $" << cost << endl;
    }
    return 0;
}
