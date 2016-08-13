#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    const int bound[4] = {10, 100, 1000, 10000};

    for (int nds; cin >> nds; )
        for (int hnd=nds/2, x=0; x<bound[hnd-1]; x++)
            for (int y=0; y<bound[hnd-1] && x*bound[hnd-1]+y>=(x+y)*(x+y); y++)
                if (x*bound[hnd-1]+y==(x+y)*(x+y))
                    cout << setw(hnd) << setfill('0') << x << setw(hnd) << setfill('0') << y << endl;

    return 0;
}
