// #sorting
#include <algorithm>
#include <iostream>
#include <memory>
using namespace std;

bool msort(int *data, uint32_t len, int *buff, uint64_t &count)
{
    if (len <= 1)
        return false;
    else {
        const uint32_t m = len / 2;
        bool s = msort(data,     m,       buff,     count);
        bool t = msort(data + m, len - m, buff + m, count);

        if (s && !t)
            copy(data + m, data + len, buff + m);
        else if (!s && !t)
            swap(data, buff);
        else if (!s) {
            copy(data, data + m, buff);
            s = true;
        }

        for (uint32_t i = 0, j = m, o = 0; i < m || j < len; o++) {
            if (i == m || (j < len && buff[i] > buff[j])) {
                data[o] = buff[j];
                count += m - i;
                j++;
            }
            else {
                data[o] = buff[i];
                i++;
            }
        }

        return !s;
    }
}

int main()
{
    unique_ptr<int[]> data(new int[1000000]),
                      buff(new int[1000000]);

    for (uint32_t n; cin >> n; ) {
        for (uint32_t i = 0; i < n; i++)
            cin >> data[i];

        uint64_t count = 0;
        msort(data.get(), n, buff.get(), count);
        cout << count << endl;
    }

    return 0;
}
