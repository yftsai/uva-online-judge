// #trivial
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<string> names;
    string query, name;

    uint32_t n;
    for (cin >> n; n > 0 && cin >> query; n--) {
        if (query == "Sleep") {
            cin >> name;
            names.emplace_back(name);
        }
        else if (query == "Kick") {
            if (!names.empty())
                names.pop_back();
        }
        else {
            if (names.empty())
                cout << "Not in a dream" << endl;
            else
                cout << names.back() << endl;
        }
    }
    return 0;
}
