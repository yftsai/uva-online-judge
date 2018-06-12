// #sort
#include <iostream>
#include <algorithm>
using namespace std;

int merge_sort(int n, int *data)
{
    int flip_count = 0, temp[n];
    if (n >= 2) {
        int m = n / 2;
        flip_count = merge_sort(m, data);
        flip_count += merge_sort(n - m, data + m);

        for (int i = 0, j = m, k = 0; k < n; k++)
            if (j == n || (i < m && data[i] <= data[j]))
                temp[k] = data[i++];
            else {
                temp[k] = data[j++];
                flip_count += (m - i);
            }
        copy(temp, temp + n, data);
    }
    return flip_count;
}

int main()
{
    for (int n; cin >> n; ) {
        int data[n];
        for (int &i: data)
            cin >> i;
        cout << "Minimum exchange operations : " << merge_sort(n, data) << endl;
    }
    return 0;
}
