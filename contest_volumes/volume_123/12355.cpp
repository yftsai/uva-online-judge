#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    vector<uint32_t> prime;
    prime.push_back(2);
    for (uint32_t i=3; i<uint32_t(1E7); i+=2) {
        bool is_prime = true;
        for (size_t j=0; is_prime && j<prime.size() && prime[j]<sqrt(i)+1; j++)
            is_prime = (i%prime[j]!=0);
        if (is_prime)
            prime.push_back(i);
    }

    for (uint64_t q; (cin >> q) && q!=0; ) {
        for (; q%2==0; q/=2)
            ;
        uint64_t np = 2;
        for (size_t i=1; i<prime.size() && prime[i]<=sqrt(q)+1; i++) {
            uint32_t exp = 0;
            for (; q%prime[i]==0; q/=prime[i], exp++)
                ;
            np *= (2*exp+1);
        }
        if (q!=1)
            np *= 3;

        cout << np << endl;
    }

    return 0;
}
