#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>
using namespace std;

int64_t powmod(int b, int p, int m)
{
    int64_t r=1, v=b;
    for (int64_t v=b; p>0; v=(v*v)%m, p/=2)
        if (p%2==1)
            r = (r*v)%m;
    return r;
}

int main()
{
    const int range = 10*1000*1000;
    bitset<range+1> isprime;
    isprime.flip();
    for (int p = 2; p<=range; ++p)
        if (isprime.test(p))
            for (int i=p+p; i<=range; i+=p)
                isprime.reset(i);

    vector<int> prime(1, 2);
    for (int i=3; i<=range; i+=2)
        if (isprime.test(i))
            prime.push_back(i);

    const int diny = 1000000007;
    for (int n; (cin >> n) && n>0; ) {
        int64_t dm = 1;
        for (int i = 0; n/prime[i]>=2; ++i) {
            int count = 0;
            for (int j = n/prime[i]; j>0; j/=prime[i])
                count += j;
            dm = (dm * powmod(prime[i], count/2*2, diny)) % diny;
        }
        cout << dm << endl;
    }

    return 0;
}
