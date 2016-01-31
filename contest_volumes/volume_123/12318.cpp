#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
using namespace std;

int main()
{
    uint32_t m, n, k;
    vector<uint32_t> a;

    while ((cin >> n >> m) && n!=0) {
        cin >> k;
        a.resize(k+1);
        for (auto &ak: a)
            cin >> ak;

        m = m>n ? n+m%n : m;
        set<uint32_t> result;
        for (uint32_t i=0; i<=m; i++) {
            unsigned int r = 0;
            for (uint64_t j=0, b=1; j<a.size(); j++, b=(b*i)%(n+1))
                r = (r + b*a[j])%(n+1);
            result.insert(r);
        }
        cout << result.size() << endl;
    }

    return 0;
}
