// #bellman_ford
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct road
{
    uint16_t src;
    uint16_t dst;
    int amount;
};

int main()
{
    vector<int> busyness(200);
    vector<road> roads(200 * 200);
    vector<int> amounts(200);
    constexpr int unreachable = numeric_limits<int>::max();
    constexpr int neg_inf = numeric_limits<int>::min();

    uint16_t n;
    for (uint32_t set_number = 1; cin >> n; ++set_number) {
        busyness.resize(n);
        for (auto &b: busyness)
            cin >> b;

        uint32_t r;
        cin >> r;
        roads.resize(r);
        for (auto &r: roads) {
            cin >> r.src >> r.dst;
            --r.src;
            --r.dst;
            const int d = busyness[r.dst] - busyness[r.src];
            r.amount = d * d * d;
        }

        amounts.assign(n, unreachable);
        if (n > 0)
            amounts[0] = 0;
        for (uint32_t i = 0; i < n; ++i) {
            for (const auto &road: roads) {
                const int a = amounts[road.src] + road.amount;

                if (amounts[road.src] == neg_inf)
                    amounts[road.dst] = neg_inf;
                else if (amounts[road.src] != unreachable
                    && a < amounts[road.dst])
                    amounts[road.dst] = (i + 1 == n) ? neg_inf : a;
            }
        }

        uint32_t q, junction;
        cout << "Set #" << set_number << endl;
        for (cin >> q; q > 0 && cin >> junction; --q)
            if (amounts[junction - 1] < 3 || amounts[junction - 1] == unreachable)
                cout << "?" << endl;
            else
                cout << amounts[junction - 1] << endl;
    }

    return 0;
}
