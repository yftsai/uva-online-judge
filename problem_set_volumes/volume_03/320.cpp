// #easy
#include <iostream>
#include <string>
#include <array>
using namespace std;

int main()
{
    const char mark = 'X';
    int test_number = 1, test_count, x, y;
    string path;
    array<string, 32> bitmap;
    for (cin >> test_count; test_number <= test_count && cin >> x >> y >> path; ++test_number) {
        for (string &row: bitmap)
            row.assign(32, '.');
        for (char dir: path)
            if (dir == 'N')
                bitmap[y++][x] = mark;
            else if (dir == 'E')
                bitmap[y - 1][x++] = mark;
            else if (dir == 'W')
                bitmap[y][--x] = mark;
            else if (dir == 'S')
                bitmap[--y][x - 1] = mark;

        cout << "Bitmap #" << test_number << endl;
        for (auto it = bitmap.rbegin(); it != bitmap.rend(); ++it)
            cout << *it << endl;
        cout << endl;
    }

    return 0;
}
