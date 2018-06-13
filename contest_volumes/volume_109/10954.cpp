// #huffman_coding
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int numbers[5000];
    for (int n; cin >> n && n != 0; ) {
        for (int i = 0; i < n; i++)
            cin >> numbers[i];

        int *qbegin = numbers, *qend = numbers + n;
        sort(qbegin, qend);
        int *rbegin = numbers, *rend = numbers;     // queue r is initially empty

        int cost = 0;
        for (int i = 1; i < n; i++) {
            // C++11 sequenced-before rule is required
            *rend = (rbegin == rend || (qbegin != qend && *qbegin < *rbegin)) ? *(qbegin++) : *(rbegin++);
            *rend += (rbegin == rend || (qbegin != qend && *qbegin < *rbegin)) ? *(qbegin++) : *(rbegin++);
            cost += *(rend++);
        }
        cout << cost << endl;
    }
    return 0;
}
