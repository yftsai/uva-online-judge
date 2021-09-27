// #trivial
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

int main()
{
    string unit_ings = "MARGARITA";     // ingredients
    array<uint16_t, 26> unit_counts;

    unit_counts.fill(0);
    for (const char c: unit_ings)
        unit_counts[c - 'A']++;
    sort(unit_ings.begin(), unit_ings.end());
    unit_ings.erase(unique(unit_ings.begin(), unit_ings.end()), unit_ings.end());

    uint32_t n;
    string ingredients;
    array<uint16_t, 26> counts;
    for (cin >> n; n > 0 && cin >> ingredients; n--) {
        counts.fill(0);
        for (const char c: ingredients)
            counts[c - 'A']++;

        uint16_t count = ingredients.size();
        for (uint16_t i = 0; i < unit_ings.size(); i++) {
            const char j = unit_ings[i] - 'A';
            count = min<uint16_t>(counts[j] / unit_counts[j], count);
        }
        cout << count << endl;
    }

    return 0;
}
