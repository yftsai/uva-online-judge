// #trivial
#include <iostream>
using namespace std;

int main()
{
    int b, s;

    for (int n=1; (cin >> b >> s) && (b!=0 && s!=0); n++) {
        cout << "Case " << n << ": ";
        if (s==0 || b==0 || b-1==0)
            cout << ":-\\" << endl;
        else if (s-1 >= b-1)
            cout << ":-|" << endl;
        else if (s>b)
            cout << ":-)" << endl;
        else
            cout << ":-(" << endl;
    }
    return 0;
}
