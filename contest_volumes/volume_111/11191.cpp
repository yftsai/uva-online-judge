// #prime_factorization
#include <iostream>
#include <bitset>
#include <map>
using namespace std;

int main()
{
    uint32_t primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    constexpr size_t prime_count = sizeof(primes)/sizeof(primes[0]);
    typedef bitset<1 + prime_count> factors;
    auto compare = [](const factors &f, const factors &g) { return f.to_ulong() < g.to_ulong(); };

    int t, n;
    for (cin >> t; t > 0 && cin >> n; t--) {
        map<factors, uint64_t, decltype(compare)> counts(compare);
        uint64_t zero_count = 0;
        int64_t v;
        for (int i = 0; i < n && cin >> v; i++) {
            factors fs;
            if (v < 0)
                v = -v, fs.flip(0);
            for (size_t j = 0; j < prime_count && v >= primes[j]; j++)
                for (; v % primes[j] == 0; v = v/primes[j])
                    fs.flip(1 + j);
            if (v == 0)
                zero_count++;
            else if (counts.find(fs) == counts.end())
                counts[fs] = 1;
            else
                counts[fs]++;
        }

        uint64_t x = zero_count * (zero_count - 1) / 2 + zero_count * (n - zero_count);
        for (auto &p: counts)
            x += p.second * (p.second - 1) / 2;

        uint64_t y = zero_count * (zero_count - 1) / 2 * (zero_count - 2) /3
            + zero_count * (zero_count - 1) / 2 * (n - zero_count)
            + (n - zero_count) * (n - zero_count - 1) / 2 * zero_count;
        for (auto p = counts.begin(); p != counts.end(); p++)
            for (auto q = p; q != counts.end(); q++) {
                factors r = p->first ^ q->first;
                auto it = counts.find(r);
                if (compare(r, q->first) || it == counts.end())
                    ;
                else if (p->first == r)
                    y += p->second * (p->second - 1) * (p->second - 2) / 6;
                else if (p->first == q->first)
                    y += p->second * (p->second - 1) / 2 * it->second;
                else if (q->first == r)
                    y += q->second * (q->second - 1) / 2 * p->second;
                else
                    y += p->second * q->second * it->second;
            }

        cout << x << " " << y << endl;
    }
    return 0;
}
