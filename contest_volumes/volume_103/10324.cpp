// #easy
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string s;
    vector<uint32_t> counts;
    for (uint32_t case_number = 1, n, i, j; cin >> s >> n; case_number++, counts.clear()) {
        cout << "Case " << case_number << ":" << endl;
        counts.reserve(s.size());
        for (uint32_t k = 0; k < n && cin >> i >> j; k++) {
            if (i > j)
                swap(i, j);
            while (counts.size() <= j)
                counts.push_back(counts.back() + s[counts.size()] - '0');
            uint32_t b = (i == 0) ? 0 : counts[i - 1], e = counts[j];
            cout << ((e == b || e - b == j - i + 1) ? "Yes" : "No") << endl;
        }
    }

    return 0;
}
