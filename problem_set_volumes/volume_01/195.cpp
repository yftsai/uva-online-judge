#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

bool compare(char c, char d)
{
    char lower_c = tolower(c);
    char lower_d = tolower(d);
    return (lower_c == lower_d) ? (c < d) : (lower_c < lower_d);
}

int main()
{
    string line;
    getline(cin, line);
    for (int n = stoi(line); n > 0; n--) {
        getline(cin, line);
        sort(line.begin(), line.end(), compare);
        do {
            cout << line << endl;
        } while (next_permutation(line.begin(), line.end(), compare));
    }

    return 0;
}
