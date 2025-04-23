// #easy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // It can be precomputed and verified that the sequence contains a cycle:
    // 0, 1, ...., 0, 1, ...
    vector<uint32_t> numbers;
    uint32_t f = 0, g = 1;
    uint32_t m = 1u << 19;
    numbers.reserve(786434);
    numbers.push_back(f);
    numbers.push_back(g);
    do {
        swap(f, g);
        numbers.push_back(g = (g + f) % m);
    } while (f != 0 || g != 1);
    numbers.pop_back();
    numbers.pop_back();

    for (uint32_t n; cin >> n >> m; )
        cout << (numbers[n % numbers.size()] % (1u << m)) << endl;

    return 0;
}
