// #trivial
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint32_t> catalogs;
    for (uint32_t m, n; cin >> m >> n && (m > 0 || n > 0); ) {
        catalogs.resize(m);
        for (auto &c: catalogs)
            cin >> c;
        uint32_t count = 0;
        for (uint32_t i = 0, j = 0, c; i < n && cin >> c; ++i) {
            for (; j < m && c > catalogs[j]; ++j)
                ;
            count += (j < m && catalogs[j] == c) ? 1 : 0;
        }
        cout << count << endl;
    }

    return 0;
}
