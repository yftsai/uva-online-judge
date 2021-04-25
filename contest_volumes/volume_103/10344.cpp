// #easy
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

bool fit(const array<uint16_t, 5> &as, int32_t goal, uint16_t i, int32_t value)
{
    if (i == as.size())
        return value == goal;
    else {
        for (int32_t v: { value + as[i], value - as[i], value * as[i] })
            if (fit(as, goal, i + 1, v))
                return true;
        return false;
    }
}

int main()
{
    array<uint16_t, 5> as;

    while (all_of(as.begin(), as.end(), [](uint16_t &a) { return bool(cin >> a); })
        && any_of(as.begin(), as.end(), [](uint16_t a) { return a != 0; })) {
        sort(as.begin(), as.end());
        bool is_possible = false;
        do {
            is_possible = fit(as, 23, 1, as[0]);
        } while (!is_possible && next_permutation(as.begin(), as.end()));

        cout << (is_possible ? "Possible" : "Impossible") << endl;
    }

    return 0;
}
