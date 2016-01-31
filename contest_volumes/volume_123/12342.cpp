#include <iostream>
#include <climits>
using namespace std;

int main()
{
    const unsigned int level[5] = { 180*1000, 300*1000, 400*1000, 300*1000, UINT_MAX };
    const unsigned int rate[5] = { 0, 10, 15, 20, 25};
    unsigned int t, k;

    cin >> t;
    for (unsigned int i=1; i<=t; i++) {
        cin >> k;

        unsigned int ti = 0, tf = 0;
        for (int j=0; j<5; j++) {
            unsigned int taxable = (k <= level[j]) ? k : level[j];
            k -= taxable;
            tf += (taxable%100)*rate[j];
            ti += taxable/100*rate[j] + tf/100;
            tf %= 100;
        }

        if (ti==0 && tf==0)
            ;
        else if (ti<2000)
            ti = 2000;
        else if (tf>0)
            ti++;

        cout << "Case " << i << ": " << ti << endl; 
    }

    return 0;
}
