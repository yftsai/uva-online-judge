// #easy
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else {
        for (; a % b > 0; swap(a, b))
            a %= b;
        return b;
    }
}

int main()
{
    vector<int> numbers;

    for (int n; (cin >> n) && (n != 0); ) {
        numbers.clear();
        numbers.push_back(n);
        while ((cin >> n) && (n != 0))
            numbers.push_back(n);

        int d = 0;
        for (auto p = numbers.begin(); p != numbers.end(); p++)
            for (auto q = next(p); q != numbers.end(); q++)
                d = gcd(d, abs(*p - *q));
        cout << d << endl;
    }

    return 0;
}
