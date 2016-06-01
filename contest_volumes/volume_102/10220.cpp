#include <iostream>
#include <vector>
using namespace std;

int main()
{
    unsigned int sum[1001];
    sum[0] = 1;

    const unsigned int base = 1000000;
    vector<unsigned int> fact(1, 1);
    for (unsigned int i=1; i<=1000; ++i){
        unsigned int c = 0;
        for (size_t j=0; j<fact.size(); ++j){
            fact[j] = fact[j]*i + c;
            c = fact[j]/base;
            fact[j] %= base;
        }
        if (c>0)
            fact.push_back(c);

        sum[i] = 0;
        for (auto f: fact)
            for (auto s = f; s>0; s/=10)
                sum[i]+= s%10;
    }

    for (unsigned int i; cin >> i; )
        cout << sum[i] << endl;

    return 0;
}
