// #dynamic_programming
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int16_t get_total(uint16_t price, uint16_t tea_charge)
{
    uint16_t t = price + tea_charge;
    return t + t / 10 + ((t % 10 == 0) ? 0 : 1);
}

int main()
{
    cout.setf(ios::fixed);
    cout.precision(2);

    vector<vector<int16_t>> fav_vals;   // dish_count, total_price -> favour value
    for (int16_t n, x, t, k; cin >> n >> x >> t >> k && n > 0; ) {
        const int16_t budget = x * (n + 1), tea_charge = t * (n + 1);
        const int16_t approx_price = budget / 1.1 - tea_charge;
        const int16_t approx_prices[] = { int16_t(approx_price + 1),
                                          approx_price,
                                          int16_t(approx_price - 1) };
        auto pred = [&](int16_t p) { return get_total(p, tea_charge) <= budget; };
        const int16_t max_cost = *find_if(begin(approx_prices), end(approx_prices), pred);

        fav_vals.assign(min(k * 2u, 2u * (n + 1u)) + 1u, vector<int16_t>());
        fav_vals[0].push_back(0);
        for (uint16_t i = 0, p; i < k && cin >> p; ++i) {
            uint16_t fsum = 0;
            for (uint16_t j = 0, f; j < n + 1u && cin >> f; ++j)
                fsum += f;

            for (uint16_t j = 0; j < 2; ++j)
                for (int16_t dc = fav_vals.size() - 2; dc >= 0; --dc)
                    for (int16_t cost = min<int16_t>(fav_vals[dc].size() - 1, max_cost - p); cost >= 0; --cost)
                        if (fav_vals[dc][cost] >= 0) {
                            if (fav_vals[dc + 1].size() <= uint16_t(cost) + p)
                                fav_vals[dc + 1].resize(cost + p + 1u, -1);

                            fav_vals[dc + 1][cost + p] = max<int16_t>(fav_vals[dc + 1][cost + p],
                                                                      fav_vals[dc][cost] + fsum);
                        }
        }

        int16_t fav_val = 0;
        for (auto &fvs: fav_vals)
            for (auto &fv: fvs)
                fav_val = max(fav_val, fv);
        cout << fav_val / double(n + 1) << endl;
    }

    return 0;
}
