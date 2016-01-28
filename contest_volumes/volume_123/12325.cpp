#include <iostream>
#include <cstdint>
#include <limits>
#include <cmath>
using namespace std;

int main()
{
    int t, i;
    int64_t n, s1, v1, s2, v2;
    const int32_t threshold = static_cast<int32_t>(sqrt(numeric_limits<int32_t>::max()));

    for (cin >> t, i=1; i<=t; ++i) {
        cin >> n >> s1 >> v1 >> s2 >> v2;

        if (v1*s2 < v2*s1)
            swap(s1, s2), swap(v1, v2);

        int64_t maxv = 0;
        if (s1 >= threshold)
            for (int64_t j=0; j<=n/s1; ++j)
                maxv = max(maxv, j*v1 + (n-j*s1)/s2*v2);
        else
            for (int64_t j=0; j<s1 && j*s2<=n; ++j)
                maxv = max(maxv, (n-j*s2)/s1*v1 + j*v2);

        cout << "Case #" << i << ": " << maxv << endl;
    } 

    return 0;
}
