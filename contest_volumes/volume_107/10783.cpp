// #trivial
#include <iostream>
using namespace std;

int main()
{
    int t, a, b;

    cin >> t;
    for (int i=1; i<=t; i++){
        cin >> a >> b;
        a = a%2==0 ? a+1 : a;
        b = b%2==0 ? b-1 : b;
        cout << "Case " << i << ": " << (a+b)*((b-a)/2+1)/2 << endl;
    }

    return 0;
}
