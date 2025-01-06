// #easy
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

void parse(const string &line, vector<pair<string, string>> &dict)
{
    dict.clear();
    for (uint16_t i = 1, len; i < line.size() && line[i] != '}'; i += 1 + len) {
        for (len = 1; line[i + len] != ':'; len++)
            ;
        string key = line.substr(i, len);
        i += 1 + len;
        for (len = 1; isdigit(line[i + len]); len++)
            ;
        dict.emplace_back(move(key), line.substr(i, len));
    }
}

void print(char c, const vector<string> &keys)
{
    auto it = keys.begin();
    cout << c << *it;
    for (++it; it != keys.end(); ++it)
        cout << ',' << *it;
    cout << endl;
}

int main()
{
    vector<pair<string, string>> odict, ndict;
    vector<string> add, rmv, chg;

    uint16_t t = 0;
    string line;
    for (cin >> t; t > 0 && cin >> line; t--) {
        odict.clear();
        parse(line, odict);
        sort(odict.begin(), odict.end());

        cin >> line;
        ndict.clear();
        parse(line, ndict);
        sort(ndict.begin(), ndict.end());

        add.clear();
        rmv.clear();
        chg.clear();
        for (uint16_t i = 0, j = 0; i < odict.size() || j < ndict.size(); )
            if (i == odict.size())
                add.emplace_back(move(ndict[j++].first));
            else if (j == ndict.size())
                rmv.emplace_back(move(odict[i++].first));
            else {
                auto cmp = odict[i].first.compare(ndict[j].first);
                if (cmp < 0)
                    rmv.emplace_back(move(odict[i++].first));
                else if (cmp == 0) {
                    if (odict[i].second != ndict[j].second)
                        chg.emplace_back(move(odict[i].first));
                    i++;
                    j++;
                }
                else
                    add.emplace_back(move(move(ndict[j++].first)));
            }

        if (add.size() > 0)
            print('+', add);
        if (rmv.size() > 0)
            print('-', rmv);
        if (chg.size() > 0)
            print('*', chg);
        if (add.size() == 0 && rmv.size() == 0 && chg.size() == 0)
            cout << "No changes" << endl;
        cout << endl;
    }

    return 0;
}
