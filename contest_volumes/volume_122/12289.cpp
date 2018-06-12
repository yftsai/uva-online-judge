// #trivial
#include <iostream>
using namespace std;

int main()
{
    int n;
    char word[6];
    for (cin >> n; n > 0 && cin >> word; n--) {
        if (word[3] != '\0')
            cout << 3 << endl;
        else {
            int d = 0;
            for (int i = 0; i < 3; i++)
                d += (word[i] == "one"[i]) ? 0 : 1;
            cout << (d <= 1 ? 1 : 2) << endl;
        }
    }

    return 0;
}
