// #easy
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    const auto f = [](uint32_t x) { return x * x * x; };
    vector<uint32_t> cubic_values;
    do {
        cubic_values.push_back(f(cubic_values.size()));
    } while (cubic_values.size() < 2
        || cubic_values[cubic_values.size() - 1] - cubic_values[cubic_values.size() - 2] < 10000);

    for (uint16_t n; cin >> n && n != 0; ) {
        uint16_t x = 1, y = 2;
        while (y < cubic_values.size() && x < y && cubic_values[x] + n != cubic_values[y])
            if (cubic_values[x] + n < cubic_values[y])
                ++x;
            else
                ++y;

        if (y >= cubic_values.size() || x >= y)
            cout << "No solution" << endl;
        else
            cout << y << " " << x << endl;
    }

    return 0;
}
