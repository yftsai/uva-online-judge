// A simpler solution is testing integers up to sqrt(# of coconuts).
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;

bool validate(int n, int m)
{
    for (int i = 0; i < m; i++) {
        if (n % m != 1)
            return false;
        n -= 1;
        n = n / m * (m - 1);
    }
    return n % m == 0;
}

int main()
{
    vector<int> primes = {2, 3};
    for (int i = 5; i < int(sqrt(numeric_limits<int>::max())) + 1; i += 2) {
        auto end = upper_bound(primes.begin(), primes.end(), int(sqrt(i)) + 1);
        if (all_of(primes.begin(), end, [i](int p) { return i % p != 0; }))
            primes.push_back(i);
    }

    vector<int> facts;
    vector<int> heap;
    for (int n; cin >> n && n >= 0; ) {
        facts.clear();
        heap.clear();
        set<int> ms;
        if (n > 1) {
            int m = n - 1;
            auto end = upper_bound(primes.begin(), primes.end(), int(sqrt(m)) + 1);
            for (auto it = primes.begin(); it != end; ++it) {
                if (m % *it == 0)
                    facts.push_back(*it);
                while (m % *it == 0)
                    m /= *it;
            }
            if (m > 1)
                facts.push_back(m);
            heap.emplace_back(n - 1);
            ms.insert(n - 1);
        }

        while (heap.size() > 0 && !validate(n, heap.front())) {
            pop_heap(heap.begin(), heap.end());
            const int m = heap.back();
            heap.pop_back();
            ms.erase(m);

            if (m > 1) {
                for (auto f: facts) {
                    if (m % f == 0) {
                        auto o = m / f;
                        if (ms.find(o) == ms.end()) {
                            heap.push_back(o);
                            push_heap(heap.begin(), heap.end());
                            ms.insert(o);
                        }
                    }
                }
            }
        }

        cout << n << " coconuts, ";
        if (heap.size() == 0)
            cout << "no solution" << endl;
        else
            cout << heap[0] << " people and 1 monkey" << endl;
    }

    return 0;
}
