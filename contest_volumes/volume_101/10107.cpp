// #easy
#include <iostream>
#include <set>
using namespace std;

int main()
{
    multiset<uint32_t> smaller_values, larger_values;
    uint32_t medians[2], median_count = 0;

    for (uint x; cin >> x; ) {
        if (median_count == 0)
            medians[median_count++] = x;
        else if (median_count == 1) {
            if ((smaller_values.size() == 0 && x <= medians[0])
                || (smaller_values.size() > 0 && *smaller_values.rbegin() <= x && x <= medians[0])) {
                medians[median_count++] = medians[0];
                medians[0] = x;
            }
            else if (smaller_values.size() == 0 || (medians[0] <= x && x <= *larger_values.begin()))
                medians[median_count++] = x;
            else if (x < *smaller_values.rbegin()) {
                medians[median_count++] = medians[0];
                medians[0] = *smaller_values.rbegin();
                smaller_values.erase(--smaller_values.end());
                smaller_values.insert(x);
            }
            else {
                medians[median_count++] = *larger_values.begin();
                larger_values.erase(larger_values.begin());
                larger_values.insert(x);
            }
        }
        else if (x <= medians[0]) {
            smaller_values.insert(x);
            larger_values.insert(medians[--median_count]);
        }
        else if (medians[0] <= x && x <= medians[1]) {
            smaller_values.insert(medians[0]);
            larger_values.insert(medians[1]);
            medians[(median_count = 1) - 1] = x;
        }
        else {
            smaller_values.insert(medians[0]);
            medians[0] = medians[--median_count];
            larger_values.insert(x);
        }

        if (median_count == 1)
            cout << medians[0] << endl;
        else
            cout << (medians[0] + medians[1]) / 2 << endl;
    }

    return 0;
}
