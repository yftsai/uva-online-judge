// #easy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    cout.setf(ios::fixed);
    cout.precision(2);

    vector<int> elevations;
    vector<int> volumes;
    for (uint32_t m, n, r = 1; cin >> m >> n && m != 0 && n != 0; ++r) {
        elevations.resize(m * n);
        for (auto &e: elevations)
            cin >> e;
        sort(elevations.begin(), elevations.end());

        volumes.resize(elevations.size());
        volumes[0] = 0;
        for (size_t i = 1; i < elevations.size(); ++i)
            volumes[i] = volumes[i - 1u] + (elevations[i] - elevations[i - 1u]) * 10 * 10 * i;

        int volume;
        cin >> volume;

        size_t index = upper_bound(volumes.begin(), volumes.end(), volume) - volumes.begin();
        const double level = (index == 0) ?
            (double(volume) / 10 / 10) :
            (elevations[index - 1u] + double(volume - volumes[index - 1u]) / 10 / 10 / index);
        index = lower_bound(volumes.begin(), volumes.end(), volume) - volumes.begin();
        const double region = double(index) / m / n * 100;

        cout << "Region " << r << endl;
        cout << "Water level is " << level << " meters." << endl;
        cout << region << " percent of the region is under water." << endl;
        cout << endl;
    }

    return 0;
}
