// #trivial
#include <iostream>
#include <string>
using namespace std;

int main()
{
    const string vowels = "aeiou";
    int n;
    string names[2];
    for (cin >> n; n > 0 && cin >> names[0] >> names[1]; n--) {
        bool is_same = (names[0].size() == names[1].size());
        for (size_t i = 0; i < names[0].size() && is_same; i++)
            is_same = (names[0][i] == names[1][i])
                || (vowels.find(names[0][i]) != string::npos && vowels.find(names[1][i]) != string::npos);
        cout << (is_same ? "Yes" : "No") << endl;
    }
    return 0;
}
