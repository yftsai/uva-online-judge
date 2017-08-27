// #set_union
#include <iostream>
#include <string>
#include <set>
using namespace std;

int get_representative(int *parents, int p)
{
    if (parents[p] == p)
        return p;
    else
        return parents[p] = get_representative(parents, parents[p]);
}

int main()
{
    string line;
    getline(cin, line);
    int case_count = stoi(line);
    getline(cin, line);
    for (; case_count > 0; case_count--){
        getline(cin, line);
        const int node_count = line[0] - 'A' + 1;
        int parents[26];
        for (int i = 0; i < node_count; i++)
            parents[i] = i;

        while (getline(cin, line) && line.size() > 0)
            parents[get_representative(parents, line[0] - 'A')]= get_representative(parents, line[1] - 'A');
        for (int i = 0; i < node_count; i++)
            get_representative(parents, i);

        set<int> s(parents, parents + node_count);
        cout << s.size() << endl;
        if (case_count > 1)
            cout << endl;
    }

    return 0;
}
