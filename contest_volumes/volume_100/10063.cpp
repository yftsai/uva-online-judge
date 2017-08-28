// #easy
#include <iostream>
#include <list>
using namespace std;

void print_permutations(const char *line, list<char> &permutation)
{
    list<char>::iterator it, it2;
    if (line[0] == '\0'){
        for (char c: permutation)
            cout << c;
        cout << endl;
    }
    else {
        for (auto it = permutation.begin(); it != permutation.end(); it++) {
            it = permutation.insert(it, line[0]);
            print_permutations(line + 1, permutation);
            it = permutation.erase(it);
        }
        auto it = permutation.insert(permutation.end(), line[0]);
        print_permutations(line + 1, permutation);
        permutation.erase(it);
    }
}

int main()
{
    char line[11];
    for (bool is_first = true; cin >> line; is_first = false) {
        if (!is_first)
            cout << endl;
        list<char> permutation;
        print_permutations(line, permutation);
    }

    return 0;
}
