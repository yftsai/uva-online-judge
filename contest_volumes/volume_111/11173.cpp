// #easy
#include <iostream>
using namespace std;

int main()
{
    int case_count, n, k;
    for (cin >> case_count; case_count > 0 && cin >> n >> k; case_count--) {
        int base = 1, val = 0;
        bool is_reflected = false;
        for (int i=1; i<n; i++)
            base *= 2;
        for (int i=0; i<n; i++, base/=2) {
            val = val * 2 + (((k < base) != is_reflected) ? 0 : 1);
            is_reflected = ((k < base) != is_reflected) ? is_reflected : !is_reflected;
            k -= k < base ? 0 : base;
        }
        cout << val << endl;
    }
    return 0;
}
