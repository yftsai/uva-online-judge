// #easy
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int get_factor(const vector<int> hprimes, int h)
{
    int r = sqrt(h);
    for (size_t i = 0; i < hprimes.size() && hprimes[i] <= r; i++)
        if (h % hprimes[i] == 0)
            return hprimes[i];
    return 1;
}

int main()
{
    vector<int> hprimes;
    for (int h = 5; h <= 1001; h+=4)
        if (get_factor(hprimes, h) == 1)
            hprimes.push_back(h);

    vector<int> hsemiprimes;
    for (int h = 5; h <= 1000001; h+=4) {
        int f = get_factor(hprimes, h);
        if (f != 1 && get_factor(hprimes, h/f) == 1)
            hsemiprimes.push_back(h);
    }

    for (int h; (cin >> h) && h != 0; )
        cout << h << " " << (upper_bound(hsemiprimes.begin(), hsemiprimes.end(), h) - hsemiprimes.begin()) << endl;

    return 0;
}
