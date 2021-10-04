// #trivial
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    map<string, vector<string>> dict;
    string word, key;

    while (cin >> word && word[0] != 'X') {
        key = word;
        sort(key.begin(), key.end());
        dict[move(key)].emplace_back(move(word));
    }
    for (auto &p: dict)
        sort(p.second.begin(), p.second.end());

    while (cin >> word && word[0] != 'X') {
        key = word;
        sort(key.begin(), key.end());

        auto it = dict.find(key);
        if (it != dict.end())
            for (const auto &w: it->second)
                cout << w << endl;
        else
            cout << "NOT A VALID WORD" << endl;
        cout << "******" << endl;
    }

    return 0;
}
