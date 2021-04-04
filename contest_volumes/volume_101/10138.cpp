// #trivial
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

struct record
{
    uint32_t time;
    bool is_exit;
    int location;

    record(uint32_t t, bool is_exit, int loc):
        time(t), is_exit(is_exit), location(loc)
    {}


    bool operator<(const record &r) const
    {
        return time < r.time;
    }
};

int main()
{
    string line, number, direction;

    getline(cin, line);
    int test_count = stoi(line);

    for (getline(cin, line); test_count > 0; --test_count) {
        getline(cin, line);
        stringstream ss(line);

        array<uint32_t, 24> rates;
        for (auto &r: rates)
            ss >> r;

        map<string, vector<record>> vehicles;
        while (getline(cin, line)) {
            ss = stringstream(line);
            uint16_t month, d, h, m;
            int location;
            char c;

            if (!(ss >> number >> month >> c >> d >> c >> h >> c >> m >> direction >> location))
                break;
            const uint32_t t = 60u * 24u * d + 60u * h + m;
            vehicles[number].emplace_back(t, direction == "exit", location);
        }

        for (auto &v: vehicles) {
            auto &records = v.second;
            sort(records.begin(), records.end());
            uint32_t bill = 0;
            for (auto it = records.begin(); it != records.end() && next(it) != records.end(); ++it) {
                const record &enter = *it;
                const record &exit = *next(it);
                if (!enter.is_exit && exit.is_exit) {
                    const uint32_t hour = (enter.time / 60u) % 24u;
                    bill += rates[hour] * abs(exit.location - enter.location) + 100;
                }
            }

            if (bill > 0) {
                bill += 200;
                const uint16_t cents = bill % 100;
                cout << v.first << " $" << (bill / 100) << ((cents < 10) ? ".0" : ".") << (bill % 100) << endl;
            }
        }
        if (test_count > 1)
            cout << endl;
    }

    return 0;
}
