// #trivial
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    uint32_t case_count;
    uint16_t n, h;
    string line;

    for (cin >> case_count; case_count > 0 && cin >> n >> h; case_count--) {
        line.assign(n - h, '0');
        line.resize(n, '1');
        do {
            cout << line << endl;
        } while (next_permutation(line.begin(), line.end()));

        if (case_count > 1)
            cout << endl;
    }

    return 0;
}
