#include <iostream>
using namespace std;

int main()
{
    uint32_t n, k;
    while ((cin >> n >> k) && n>0){
        k = k>(n-k) ? k : (n-k);
        uint64_t c = 1;
        for (uint32_t i=n, j=1; i>k; --i, ++j)
            c = c*i/j;
        cout << c << endl;
    }

    return 0;
}
