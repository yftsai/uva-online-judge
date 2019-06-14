// #trivial
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    string line;
    vector<int64_t> as;

    while (getline(cin, line)) {
        const int64_t x = stoi(line);

        getline(cin, line);
        stringstream ss(line);
        as.clear();
        for (int64_t a; ss >> a; )
            as.push_back(a);

        int64_t xe = 1;
        int64_t derivative = 0;
        for (size_t i = 1; i < as.size(); ++i, xe *= x)
            derivative += as[as.size() - 1 - i] * i * xe;

        cout << derivative << endl;
    }

    return 0;
}
