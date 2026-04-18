// #dynamic_programming
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    // table[i][j - i] stores the length of palindrome generated from line[i: j + 1]
    vector<vector<uint16_t>> table;
    string palin;
    for (string line; cin >> line; ) {
        const int16_t n = line.size();

        table.resize(n);
        for (int16_t i = n - 1; i >= 0; i--) {
            table[i].resize(1, 1);
            for (int16_t j = i + 1; j < n; j++) {
                if (line[i] == line[j])
                    table[i].push_back(i + 1 <= j - 1 ? table[i + 1][j - i - 2] + 2 : 2);
                else
                    table[i].push_back(min(table[i].back(), table[i + 1][j - i - 1]) + 2);
            }
        }

        palin.clear();
        for (int16_t i = 0, j = n -1; i <= j; ) {
            if (i + 1 <= j && table[i][j - i] == table[i + 1][j - i - 1] + 2) {
                palin += line[i];
                i += 1;
            }
            else if (i <= j - 1 && table[i][j - i - 1] + 2 == table[i][j - i]) {
                palin += line[j];
                j -= 1;
            }
            else {
                palin += line[i];
                i += 1;
                j -= 1;
            }
        }

        int16_t m = table[0].back();
        cout << m - n << " " << palin;
        if (m % 2 != 0)
            palin.pop_back();
        reverse(palin.begin(), palin.end());
        cout << palin << endl;
    }

    return 0;
}
