#include <iostream>
#include <vector>
#include <string>
using namespace std;

int find_and_update(vector<int> &dir, int i)
{
    if (i<0 || i>=static_cast<int>(dir.size()) || dir[i]==i)
        return i;
    else
        return (dir[i] = find_and_update(dir, dir[i]));
}

int main()
{
    vector<int> left, right;
    int s, b, l, r;

    while ((cin >> s >> b) && (s!=0 || b!=0)) {
        left.resize(s);
        right.resize(s);
        for (int i=0; i<s; i++)
            left[i] = right[i] = i;
        for (int i=0; i<b; i++) {
            cin >> l >> r;
            const int leftmost = find_and_update(left, l-2);
            const int rightmost = find_and_update(right, r);
            for (int i=l-1; i<r; i++) {
                left[i] = leftmost;
                right[i] = rightmost;
            }

            cout << (leftmost<0 ? "*" : to_string(leftmost+1));
            cout << " " << (rightmost>=s ? "*" : to_string(rightmost+1)) << endl;
        }
        cout << "-" << endl;
    }
    return 0;
}
