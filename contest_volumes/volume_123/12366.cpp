#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int hand[3];
    int &a=hand[0], &b=hand[1], &c=hand[2];

    while ((cin >> a >> b >> c) && a!=0) {
        if (b==c) swap(a, c);
        if (a==c) swap(b, c);

        if (a==b && b==c)
            ++a, ++b, ++c;
        else if (a==b)
            if (c+1<=13 && c+1!=a)
                ++c;
            else if (c+2<=13)
                c+=2;
            else if (a+1<=13)
                ++a, ++b, c=1;
            else
                a=1, b=1, c=1;
        else
            a=1, b=1, c=2;

        sort(hand, hand+3);
        if (c>13)
            cout << '*' << endl;
        else
            cout << a << " " << b << " " << c << endl;
    }
    return 0;
}
