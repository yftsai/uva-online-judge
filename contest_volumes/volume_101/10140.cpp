#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct range
{
    uint32_t first_prime;
    uint32_t last_prime;
    pair<uint32_t, uint32_t> close_pair;
    pair<uint32_t, uint32_t> distant_pair;

    range():
        first_prime(0),
        last_prime(0),
        close_pair(0, 0),
        distant_pair(0, 0)
    {}

    void add(uint32_t p);
    void add(const pair<uint32_t, uint32_t> p);
    void add(const range &r);
};

void range::add(uint32_t p)
{
    first_prime = (first_prime == 0) ? p : min(first_prime, p);
    last_prime = (last_prime == 0) ? p : max(last_prime, p);
}

void range::add(const pair<uint32_t, uint32_t> p)
{
    first_prime = (first_prime == 0) ? p.first : min(first_prime, p.first);
    last_prime = (last_prime == 0) ? p.second : max(last_prime, p.second);

    const uint32_t q = p.second - p.first;

    const uint32_t c = close_pair.second - close_pair.first;
    if (close_pair.first == 0 || q < c || (q == c && p.first < close_pair.first))
        close_pair = p;

    const uint32_t d = distant_pair.second - distant_pair.first;
    if (distant_pair.first == 0 || d < q || (d == q && p.first < distant_pair.first))
        distant_pair = p;
}

void range::add(const range &r)
{
    if (last_prime != 0 && r.first_prime != 0) {
        add(make_pair(last_prime, r.first_prime));
    }

    if (r.first_prime != 0) {
        add(r.first_prime);
        add(r.last_prime);
    }

    if (r.close_pair.first != 0) {
        add(r.close_pair);
        add(r.distant_pair);
    }
}

range compute_range(const uint32_t begin, const uint32_t end)
{
    vector<bool> is_composite(end - begin, false);

    vector<bool> is_composite_factor(uint32_t(sqrt(end)) + 1, false);
    for (uint32_t p = 3; p < is_composite_factor.size(); p += 2)
        if (!is_composite_factor[p]) {
            for (uint64_t q = uint64_t(p) * p; q < is_composite_factor.size(); q += 2 * p)
                is_composite_factor[q] = true;
            for (uint32_t q = max(p * p, ((begin + p - 1) / p / 2 * 2 + 1) * p); q < end; q += 2 * p)
                is_composite[q - begin] = true;
        }

    uint32_t last_prime = 0;
    range p;
    if (begin <= 2 && 2 < end) {
        last_prime = 2;
        p.add(2);
    }
    for (uint32_t n = max(3u, begin / 2 * 2 + 1); n < end; n += 2)
        if (!is_composite[n - begin]) {
            p.add(n);
            if (last_prime != 0)
                p.add(make_pair(last_prime, n));
            last_prime = n;
        }

    return p;
}

range get_range(uint32_t begin, uint32_t end)
{
    const uint32_t length = 1024 * 32;
    static vector<range> ranges;

    range p;
    const uint32_t m = (begin % length == 0) ? begin : min((begin / length + 1u) * length, end);
    if (begin < m)
        p = compute_range(begin, m);

    const uint32_t n = max(m, end / length * length);
    if (ranges.size() < n / length)
        ranges.resize(n / length);
    for (uint32_t i = m / length; i < n / length; ++i) {
        if (ranges[i].first_prime == 0)
            ranges[i] = compute_range(length * i, length * i + length);
        p.add(ranges[i]);
    }

    if (n < end)
        p.add(compute_range(n, end));

    return p;
}

int main()
{
    for (uint32_t l, u; cin >> l >> u; ) {
        range p = get_range((l <= 2) ? 0 : l, u + 1u);
        if (p.close_pair.first == 0)
            cout << "There are no adjacent primes." << endl;
        else
            cout << p.close_pair.first << "," << p.close_pair.second << " are closest, "
                << p.distant_pair.first << "," << p.distant_pair.second << " are most distant." << endl;
    }

    return 0;
}
