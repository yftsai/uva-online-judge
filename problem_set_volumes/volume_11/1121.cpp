// #easy
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint16_t> sequence;
    for (uint32_t n, s; cin >> n >> s; ) {
        sequence.resize(n);
        for (auto &v: sequence)
            cin >> v;

        uint32_t length = n + 1;
        for (uint32_t b = 0, e = 0, sum = 0; b < sequence.size(); sum -= sequence[b++]) {
            for (; e < sequence.size() && sum < s; e++)
                sum += sequence[e];
            if (sum >= s)
                length = min(length, e - b);
        }
        cout << ((length > n) ? 0 : length) << endl;
    }
    return 0;
}
