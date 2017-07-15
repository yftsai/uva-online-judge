// #longest_common_sequence
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string line;
    getline(cin, line);
    for (int t = stoi(line); t > 0; t--) {
        getline(cin, line);

        vector<vector<int>> table(2, vector<int>(line.size(), 0));
        for (size_t i = 0; i < line.size(); i++, table[0].swap(table[1]))
            for (size_t j = 0; j < line.size(); j++)
                if (line[line.size()-1-i] == line[j])
                    table[1][j] = (j == 0) ? 1 : (table[0][j-1] + 1);
                else
                    table[1][j] = max(table[0][j], (j == 0) ? 0 : table[1][j-1]);

        cout << ((line.size() == 0) ? 0 : table[0][line.size()-1]) << endl;
    }
    return 0;
}
