// #trivial
#include <iostream>
#include <string>
#include <sstream>
#include <set>
using namespace std;

int main()
{
    string line;
    stringstream ss;
    int n;

    getline(cin, line);
    stringstream(line) >> n;
    getline(cin, line); // empty line

    for (; n>0; n--){
        unsigned int p, t;
        getline(cin, line);
        stringstream(line) >> p >> t;

        set<int> person[p];
        while (getline(cin, line) && line!=""){
            int i, j;
            stringstream(line) >> i >> j;
            person[i-1].insert(j);
        }

        set<set<int>> opinion;
        for (unsigned int i=0; i<p; i++)
            opinion.insert(person[i]);

        cout << opinion.size() << (n>1 ? "\n" : "") << endl;
    }

    return 0;
}
