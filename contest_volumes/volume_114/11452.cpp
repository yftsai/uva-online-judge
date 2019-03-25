// #easy
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    uint32_t case_count;
    string steps;
    for (cin >> case_count; case_count > 0 && cin >> steps; --case_count) {
        uint16_t len = steps.size() / 2;
        while (!equal(steps.begin() + len * 2, steps.end(), steps.begin())
            || !equal(steps.begin(), steps.begin() + len, steps.begin() + len))
            --len;
        for (uint16_t i = 0, j = steps.size() - len * 2; i < 8; ++i, j = (j + 1) % len)
            cout << steps[j];
        cout << "..." << endl;
    }
    return 0;
}
