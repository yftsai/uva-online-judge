// #string_search
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct word
{
    string str;
    uint16_t label;

    bool operator<(const word &) const;
};

bool word::operator<(const word &w) const
{
    if (str.size() != w.str.size())
        return str.size() < w.str.size();
    int cmp = str.compare(w.str);
    if (cmp < 0)
        return true;
    else if (cmp > 0)
        return false;
    else
        return label < w.label;
}

int main()
{
    uint16_t n;
    cin >> n;
    vector<word> dict(n);
    for (uint32_t i = 0; i < n && cin >> dict[i].str; i++)
        dict[i].label = i + 1;

    sort(dict.begin(), dict.end());

    uint32_t q;
    string w;
    for (cin >> q; q > 0 && cin >> w; q--) {
        uint16_t count = 0;
        for (uint16_t i = 0; i < n && count < 10; i++)
            if (dict[i].str.find(w) != string::npos) {
                cout << (count > 0 ? " " : "") << dict[i].label;
                count++;
            }
        cout << (count == 0 ? "-1" : "") << endl;
    }

    return 0;
}
