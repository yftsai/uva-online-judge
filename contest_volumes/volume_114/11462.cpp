// #trivial
#include <iostream>
using namespace std;

int main()
{
    for (int n; cin >> n && n != 0; ) {
        int counts[101] = { 0 };
        for (int i = 0, a; i < n && cin >> a; i++)
            counts[a]++;

        bool is_first = true;
        for (int a = 1; a <= 100; a++)
            for (int i = 0; i < counts[a]; i++, is_first = false)
                cout << (is_first ? "" : " ") << a;
        cout << endl;
    }

    return 0;
}
