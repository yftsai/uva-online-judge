#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t primes[3500], prime_count = 0;
    primes[prime_count++] = 2;
    for (uint16_t i = 3, j; prime_count < 3500; i += 2) {
        for (j = 0; j < prime_count && primes[j] <= uint16_t(sqrt(i)) && i % primes[j] != 0; j++)
            ;
        if (j == prime_count || i % primes[j] != 0)
            primes[prime_count++] = i;
    }

    uint16_t positions[3502];
    for (int n = 1; n <= 3501; n++) {
        // a simple unrolled list
        const uint16_t max_size = 128;
        const uint16_t max_count = 3501 / max_size + 1;
        uint16_t lists[max_count][max_size], lengths[max_count], list_count = 0;
        for (int i = 0; i < n; i ++) {
            if (list_count == 0 || lengths[list_count - 1] == max_size)
                lengths[list_count++] = 0;
            lists[list_count - 1][ lengths[list_count - 1]++ ] = i;
        }

        for (int i = 0, p = 0; i < n-1; i++) {
            p = (p + primes[i] - 1) % (n - i);
            int list, pos;
            for (list = 0, pos = 0; p >= pos + lengths[list]; pos += lengths[list++])
                ;
            copy(lists[list] + p - pos + 1, lists[list] + lengths[list], lists[list] + p - pos);
            lengths[list]--;
        }
        for (int i = 0; i < list_count; i++)
            if (lengths[i] > 0)
                positions[n] = lists[i][0] + 1;
    }

    for (int n; cin >> n && n>0; )
        cout << positions[n] << endl;

    return 0;
}
