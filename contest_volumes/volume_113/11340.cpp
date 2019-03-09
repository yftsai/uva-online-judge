// #trivial
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    vector<int> values(128, 0);
    vector<char> paid_chars;
    string line;
    getline(cin, line);
    for (int n = stoi(line); n > 0; --n) {
        getline(cin, line);
        for (int k = stoi(line); k > 0 && getline(cin, line); --k) {
            stringstream ss(line);
            char c;
            ss >> c;
            ss >> values[c];
            paid_chars.push_back(c);
        }
        getline(cin, line);
        int paid_money = 0;
        for (int m = stoi(line); m > 0 && getline(cin, line); --m)
            for (char c: line)
                paid_money += values[c];

        int fraction = paid_money % 100;
        cout << (paid_money / 100) << "." << (fraction < 10 ? "0" : "") << fraction << "$" << endl;

        for (char c: paid_chars)
            values[c] = 0;
        paid_chars.clear();
    }

    return 0;
}
