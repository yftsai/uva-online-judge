// #trivial
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    unordered_map<string, string> dict;
    string line, eword, fword;
    while (getline(cin, line) && line.size() > 0) {
        stringstream ss(line);
        ss >> eword >> fword;
        dict[fword] = eword;
    }

    while (cin >> line) {
        auto it = dict.find(line);
        if (it == dict.end())
            cout << "eh" << endl;
        else
            cout << it->second << endl;
    }

    return 0;
}
