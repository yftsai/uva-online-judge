// #trivial
#include <iostream>
#include <string>
using namespace std;

int main()
{
    uint16_t t;
    cin >> t;
    string road;
    for (uint16_t no = 1; no <= t && cin >> road; no++) {
        uint16_t count = 0;
        for (uint16_t i = 0; i < road.size(); i++)
            if (road[i] == '-'
                && !(1 <= i && road[i - 1] == 'S')
                && !(i + 1u < road.size() && road[i + 1] == 'B')
                && !(i + 1u < road.size() && road[i + 1] == 'S')
                && !(i + 2u < road.size() && road[i + 2] == 'B'))
                count++;
        cout << "Case " << no << ": " << count << endl;
    }

    return 0;
}
