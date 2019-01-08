// #cycle_detection #easy
#include <iostream>
using namespace std;

int main()
{
    int z, i, m, l;
    for (int case_number = 1; cin >> z >> i >> m >> l && m > 0; ++case_number) {
        auto next = [&](int l) { return (z * l + i) % m; };
        for (int p = next(next(l)); l != p; l = next(l), p = next(next(p)))
            ;
        int length = 1;
        for (int p = next(l); l != p; p = next(p), ++length)
            ;
        cout << "Case " << case_number << ": " << length << endl;
    }
    return 0;
}
