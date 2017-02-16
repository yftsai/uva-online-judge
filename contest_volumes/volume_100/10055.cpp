// #trivial
#include <iostream>
using namespace std;

int main()
{
    unsigned long long v1, v2;
    while (cin >> v1 >> v2){
        if (v1>v2)
            cout << v1-v2 << endl;
        else
            cout << v2-v1 << endl;
    }

    return 0;
}
