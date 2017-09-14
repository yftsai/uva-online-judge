// #divide_and_conquer
// This solution was proposed on the forum.
// This problem is paired with problem 10730.
#include <iostream>
using namespace std;

void permutate(int *sequence, int length)
{
    int odd_count = 0;
    for (int i = length - 1; odd_count <= i; )
        if (sequence[odd_count] % 2 == 1)
            odd_count++;
        else if (sequence[i] % 2 == 0)
            i--;
        else
            swap(sequence[odd_count++], sequence[i--]);

    for (int i = 0; i < odd_count; i++)
        sequence[i] = (sequence[i] - 1) / 2;
    if (odd_count > 1)
        permutate(sequence, odd_count);
    for (int i = 0; i < odd_count; i++)
        sequence[i] = sequence[i] * 2 + 1;

    for (int i = odd_count; i < length; i++)
        sequence[i] /= 2;
    if (length - odd_count > 1)
        permutate(sequence + odd_count, length - odd_count);
    for (int i = odd_count; i < length; i++)
        sequence[i] *= 2;
}

int main()
{
    int sequence[10000];

    for (int n; cin >> n && n != 0; ) {
        for (int i = 0; i < 10000; i++)
            sequence[i] = i;
        permutate(sequence, n);
        cout << n << ":";
        for (int i = 0; i < n; i++)
            cout << " " << sequence[i];
        cout << endl;
    }
    return 0;
}
