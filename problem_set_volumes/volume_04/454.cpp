// #easy
#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

int main()
{
    string line;
    getline(cin, line);
    int test_count = stoi(line);
    getline(cin, line);
    for (; test_count > 0; test_count--){
        map<string, map<char, int>> phrases;
        while (getline(cin, line) && line[0]!='\0') {
            map<char, int> sig;
            for (auto c: line)
                if (c != ' ') {
                    if (sig.find(c) == sig.end())
                        sig[c] = 1;
                    else
                        sig[c] += 1;
                }
            phrases[line] = sig;
        }

        for (auto itl = phrases.begin(); itl != phrases.end(); itl++)
            for (auto itr = next(itl); itr != phrases.end(); itr++)
                if (itl->second == itr->second)
                    cout << itl->first << " = " << itr->first << endl;
        if (test_count > 1)
            cout << endl;
    }

    return 0;
}
