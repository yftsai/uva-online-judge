// #easy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> primes(1, 2);
    for (int i = 3; i < 5000; i++)
        if (all_of(primes.begin(), primes.end(), [i](int p) { return i % p != 0; }))
            primes.push_back(i);

    int case_count;
    cin >> case_count;
    for (int t = 1, m, n; t <= case_count && cin >> m >> n; t++) {
        vector<int> m_factors;
        vector<int> m_exps;
        for (int p: primes)
            if (m % p == 0)
                for (m_factors.push_back(p), m_exps.push_back(0); m % p == 0; m/=p)
                    m_exps.back()++;
            else if (m < p)
                break;

        vector<int> exps(m_exps.size(), 0);
        for (int i = 1; i <= n; i++)
            for (unsigned int j = 0; j < m_factors.size(); j++)
                for (int k = i; k % m_factors[j] == 0; k /= m_factors[j])
                    exps[j]++;
        for (unsigned int i = 0; i < m_factors.size(); i++)
            exps[i] /= m_exps[i];

        int exp = exps.front();
        for (int e: exps)
            exp = min(exp, e);

        cout << "Case " << t << ":" << endl;
        if (exp == 0)
            cout << "Impossible to divide" << endl;
        else
            cout << exp << endl;
    }
    return 0;
}
