// #suffix
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string necklace;
    necklace.reserve(20000);

    uint32_t n;
    for (cin >> n; n > 0 && cin >> necklace; --n) {
        const size_t size = necklace.length();
        necklace.append(necklace.c_str(), size - 1);

        size_t pos = 0;
        for (size_t i = 1, length = 0; i < size && length < size; ) {
            if (necklace[pos + length] == necklace[i + length])
                ++length;
            // All positions in [pos, pos + length] are not the start of the minimum.
            else if (necklace[pos + length] > necklace[i + length]) {
                const size_t j = i;
                i = max(pos + length + 1, j + 1);
                pos = j;
                length = 0;
            }
            // All positions in [i, i + length] are not the start of the minimum.
            else {
                i += length + 1;
                length = 0;
            }
        }
        cout << (pos + 1) << endl;
    }

    return 0;
}
