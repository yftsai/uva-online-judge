// #dynamic_programming
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    constexpr int max_n = 30001;
    uint64_t counts[max_n + 1];
    fill(counts, counts + max_n + 1, 1);
    for (int c: {5, 10, 25, 50})
        for (int v = c; v <= max_n; v ++)
            counts[v] += counts[v - c];

    for (int n; cin >> n; )
        if (counts[n] == 1)
            cout << "There is only 1 way" << " to produce " << n << " cents change." << endl;
        else
            cout << "There are " << counts[n] << " ways" << " to produce " << n << " cents change." << endl;

    return 0;
}
