// #trivial
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;

struct pilot
{
    int time;
    string name;

    bool operator<(const pilot &p) const
    {
        if (time != p.time)
            return time < p.time;
        else {
            for (size_t i = 0; i < name.size() && i < p.name.size(); ++i)
                if (tolower(name[i]) != tolower(p.name[i]))
                    return tolower(name[i]) < tolower(p.name[i]);
            return name.size() < p.name.size();
        }
    }
};

int main()
{
    vector<pilot> pilots;
    string line;

    for (; getline(cin, line); getline(cin, line)) {
        int n = stoi(line);
        pilots.resize(n);
        for (int i = 0; i < n && getline(cin, line); ++i) {
            int x, y, z;
            char name[21];
            sscanf(line.c_str(), "%s : %d min %d sec %d ms", name, &x, &y, &z);
            pilots[i].time = 1000 * (60 * x + y) + z;
            pilots[i].name = name;
        }

        sort(pilots.begin(), pilots.end());
        for (int i = 1, j = 0; i <= (n + 1) / 2; ++i) {
            cout << "Row " << i << endl;
            for (; j < int(pilots.size()) && j < i * 2; ++j)
                cout << pilots[j].name << endl;
        }
        cout << endl;
    }
    return 0;
}
