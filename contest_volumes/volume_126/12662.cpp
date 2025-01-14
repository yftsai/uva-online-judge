// #easy
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class direction { left, right };

void print(direction d, uint16_t dis, const string &n)
{
    for (uint16_t i = 0; i < dis; i++)
        cout << (d == direction::left ?  "left" : "right") << " of ";
    cout << n << endl;
}

int main()
{
    vector<string> names;
    vector<uint16_t> indexes;

    uint16_t n;
    cin >> n;

    names.resize(n);
    for (auto &n: names)
        cin >> n;
    for (uint16_t i = 0; i < n; i++)
        if (names[i] != "?")
            indexes.push_back(i);

    uint16_t q, p;
    for (cin >> q; q > 0 && cin >> p; q--) {
        auto it = lower_bound(indexes.begin(), indexes.end(), p - 1);

        if (it == indexes.end()) {
            uint16_t ld = p - 1 - *(--it);
            print(direction::right, ld, names[*it]);
        }
        else if (*it == p - 1)
            cout << names[*it] << endl;
        else if (it == indexes.begin()) {
            uint16_t rd = *it - p + 1;
            print(direction::left, rd, names[*it]);
        }
        else {
            uint16_t ri = *it;
            uint16_t rd = ri - p + 1;
            uint16_t li = *(--it);
            uint16_t ld = p - 1 - li;

            if (ld == rd)
                cout << "middle of " << names[li] << " and " << names[ri] << endl;
            else if (ld < rd)
                print(direction::right, ld, names[li]);
            else
                print(direction::left, rd, names[ri]);
        }
    }

    return 0;
}
