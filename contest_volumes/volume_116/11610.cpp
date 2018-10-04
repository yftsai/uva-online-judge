// #prefix_sum
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct segment
{
    static const int max_size = 256;
    int size, sum;
    int numbers[max_size], factor_counts[max_size];

    segment();
};

segment::segment():
    size(0),
    sum(0)
{}

bool is_prime(const vector<int> &primes, int n)
{
    for (size_t i = 0; i < primes.size() && primes[i] * primes[i] <= n; i++)
        if (n % primes[i] == 0)
            return false;
    return true;
}

int count_factors(const vector<int> &primes, int n)
{
    int count = 0;
    for (size_t i = 0; i < primes.size() && primes[i] * primes[i] <= n; i++)
        for (; n % primes[i] == 0; count++)
            n /= primes[i];
    return count + (n == 1 ? 0 : 1);
}

int main()
{
    vector<int> primes(1, 2);
    for (int i = 3; i < 3163; i += 2)
        if (is_prime(primes, i))
            primes.push_back(i);

    vector<segment> rprimes;
    for (int n = 1000010; n < 10 * 1000 * 1000; n += 10) {
        int r = 0;
        for (int m = n; m > 0; m /= 10)
            r = r * 10 + m % 10;
        if (is_prime(primes, r)) {
            if (rprimes.size() == 0 || rprimes.back().size == segment::max_size)
                rprimes.emplace_back();
            segment &s = rprimes.back();
            s.numbers[s.size] = n;
            s.factor_counts[s.size] = count_factors(primes, n);
            s.sum += s.factor_counts[s.size++];
        }
    }

    char c;
    for (int v; cin >> c >> v; ) {
        if (c == 'q') {
            int index = 0, sum = 0;
            auto it = rprimes.begin();
            for (; it != rprimes.end() && index + it->size <= v; it++)
                index += it->size, sum += it->sum;
            for (int *p = it->factor_counts; index <= v; index++, p++)
                sum += *p;
            cout << sum << endl;
        }
        else {
            auto it = rprimes.begin();
            for (; it != rprimes.end() && (it->size == 0 || it->numbers[it->size - 1] < v); it++)
                ;
            int count = 0;
            for (int i = 0; i < it->size; i++)
                if (it->numbers[i] == v) {
                    it->sum -= it->factor_counts[i];
                    count++;
                }
                else if (it->numbers[i] > v) {
                    it->numbers[i - count] = it->numbers[i];
                    it->factor_counts[i - count] = it->factor_counts[i];
                }
            it->size -= count;
        }
    }

    return 0;
}
