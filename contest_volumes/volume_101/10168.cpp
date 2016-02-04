#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Goldbach's conjecture: Every even integer greater than 2 can be expressed as the sum of two primes. 

bool is_prime(const vector<int> &prime, int n)
{
    for (auto &p: prime)
        if (p>int(sqrt(n)))
            break;
        else if (n%p==0)
            return false;
    return true;
}

int main()
{
    const int N = 10*1000*1000;
    vector<int> prime(1, 2);
    for (int i=3; i<=(int)sqrt(N); i+=2)
        if (is_prime(prime, i))
            prime.push_back(i);

    for (int i; cin >> i;) {
        if (i<8)
            cout << "Impossible." << endl;
        else {
            int p = (i%2==0) ? 2 : 3;
            cout << 2 << " " << p;
            i -= 2 + p;
            for (p = i>4 ? 3 : 2; !(is_prime(prime, p) && is_prime(prime, i-p)); p+=2)
                ;
            cout << " " << p << " " << (i-p) << endl;
        }
    }
    
    return 0;
}
