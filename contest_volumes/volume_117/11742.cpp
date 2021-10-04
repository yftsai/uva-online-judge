// #easy
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
using namespace std;

struct constraint
{
    uint16_t a, b;
    int16_t c;
};

int main()
{
    vector<uint16_t> group;
    vector<int16_t> seats;
    vector<constraint> constraints;

    for (uint16_t n, m; cin >> n >> m && n > 0; ) {
        group.resize(n);
        iota(group.begin(), group.end(), 0);

        constraints.resize(m);
        for (auto &c: constraints)
            cin >> c.a >> c.b >> c.c;

        uint16_t count = 0;
        seats.resize(n);
        do {
            for (uint16_t s = 0; s < n; s++)
                seats[ group[s] ] = s;

            bool valid = true;
            for (uint16_t i = 0; i < constraints.size() && valid; i++) {
                const auto &c = constraints[i];
                if (c.c < 0)
                    valid = abs(seats[c.a] - seats[c.b]) >= -c.c;
                else
                    valid = abs(seats[c.a] - seats[c.b]) <= c.c;
            }

            if (valid)
                count++;
        } while (next_permutation(group.begin(), group.end()));

        cout << count << endl;
    }

    return 0;
}
