// #trivial
#include <iostream>
using namespace std;

int main()
{
    int ncases;
    for (cin >> ncases; ncases>0; --ncases){
        int h, f;
        cin >> h >> f;
        for (; f>0; --f){
            for (int i=1; i<=h; ++i){
                for (int j=0; j<i; ++j)
                    cout << i;
                cout << endl;
            }
            for (int i=h-1; i>=1; --i){
                for (int j=0; j<i; ++j)
                    cout << i;
                cout << endl;
            }
            if (f>1)
                cout << endl;
        }

        if (ncases>1)
            cout << endl;
    }
    return 0;
}
