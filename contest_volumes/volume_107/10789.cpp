#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

bool is_prime(vector<int> &prime, int n)
{
    if (n==1)
        return false;
    else if (binary_search(prime.begin(), prime.end(), n))
        return true;
    else {
        for (vector<int>::iterator p = prime.begin(); p != prime.end(); p++)
            if (n % *p == 0)
                return false;
        return true;
    }
}

int main()
{
    int t;
    string line;
    vector<int> prime;

    prime.push_back(2);
    for (int i=3; i<=2001; i+=2)
        if (is_prime(prime, i))
            prime.push_back(i);

    cin >> t;
    for (int i=1; i<=t; i++){
        map<char, int> freq;
        cin >> line;
        for (string::iterator it = line.begin(); it != line.end(); it++)
            freq[*it]++;

        cout << "Case " << i << ": ";
        bool empty = true;
        for (map<char, int>::iterator it = freq.begin(); it != freq.end(); it++)
            if (is_prime(prime, it->second)){
                cout << it->first;
                empty = false;
            }
        if (empty)
            cout << "empty" << endl;
        else
            cout << endl;
    }

    return 0;
}
