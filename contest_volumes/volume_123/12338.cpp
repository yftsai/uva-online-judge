#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int t, x, n, q, i, j;

    for (cin >> t, x = 1; x<=t; x++) {
        cin >> n;
        vector<string> word(n);
        for (auto &w: word)
            cin >> w;
        cout << "Case " << x << ":" << endl;
        for (cin >> q; q > 0 && cin >> i >> j; q--) {
            size_t degree = 0;
            const string &wi = word[i-1], &wj = word[j-1];
            for (degree = 0; degree < wi.size() && degree < wj.size() && wi[degree] == wj[degree]; ++degree)
                ;
            cout << degree << endl;
        }
    }

    return 0;
}
