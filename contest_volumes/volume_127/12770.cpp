// #easy
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    for (string line; cin >> line && line != "#"; ) {
        sort(line.begin(), line.end());
        uint16_t length = 0;
        for (uint16_t i = 0; i < line.size(); i++)
            if (i + 1 >= line.size())
                line[length++] = line[i];
            else if (line[i] == line[i + 1])
                i++;
            else
                line[length++] = line[i];
        line.resize(length);

        if (line.size() == 1)
            line.clear();
        else if (line.size() > 1)
            line.pop_back();
        cout << line << endl;
    }

    return 0;
}
