// #trivial
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string move;
    for (int ncase = 1; getline(cin, move); ++ncase) {
        int puzzle[9] = {0};

        for (char c: move) {
            const int x=(c-'a')%3, y=(c-'a')/3;
            for (int i=max(0, x-1); i<=min(2, x+1); ++i)
                for (int j=max(0, y-1); j<=min(2, y+1); ++j)
                    if (i==x || j==y)
                        (++puzzle[i+j*3]) %= 10;
        }

        cout << "Case #" << ncase << ":" << endl;
        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j)
                cout << (j>0 ? " " : "") << puzzle[3*i+j];
            cout << endl;
        }
    }

    return 0;
}
