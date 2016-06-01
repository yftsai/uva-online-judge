#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    const int maxv = 20000000;
    vector<bool> prime;
    vector<int> pair;
    
    prime.resize(maxv+1, true);
    for (int i=2; i<=sqrt(maxv); i++)
        if (prime[i])
            for (int j=i*2; j<=maxv; j+=i)
                prime[j] = false;

    for (int i=3; i<=maxv; i++)
        if (prime[i] && prime[i+2])
            pair.push_back(i);
    
    for (int s; cin >> s;)
        cout << "(" << pair[s-1] << ", " << pair[s-1]+2 << ")" << endl;

    return 0;
}
