// #trivial
#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

int main()
{
    string line;

    for (bool is_first_case = true; getline(cin, line); is_first_case = false) {
        map<char, int> freqs;
        for (char c: line)
            if (c != '\n' && c != '\r') {
                if (freqs.find(c) == freqs.end())
                    freqs[c] = 1;
                else
                    freqs[c]++;
            }

        map<int, set<char>> order;
        for (auto &p: freqs)
            order[p.second].insert(p.first);

        if (!is_first_case)
            cout << endl;
        for (auto it = order.begin(); it != order.end(); it++)
            for (auto rit = it->second.rbegin(); rit != it->second.rend(); rit++)
                cout << int(*rit) << " " << it->first << endl;
    }

    return 0;
}
