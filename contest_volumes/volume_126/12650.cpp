// #trivial
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<bool> returned;
    for (uint16_t n, r; cin >> n >> r; ) {
        returned.assign(n, false);
        for (uint16_t i = 0, v; i < r && cin >> v; i++)
            returned[v - 1] = true;
        if (n == r)
            cout << '*' << endl;
        else {
            for (uint16_t i = 0; i < n; i++)
                if (!returned[i])
                    cout << i + 1 << " ";
            cout << endl;
        }
    }

    return 0;
}
