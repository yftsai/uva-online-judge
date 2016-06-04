// #sort
#include <iostream>
using namespace std;

int msort(int *a, int size, int *b)
{
    if (size<=1)
        return 0;
    else {
        int i = 0, j = size/2;
        int cnt = msort(a, j, b) + msort(a+j, size-j, b+j);
        for (int k = 0; k<size; k++)
            if (j==size || (i!=size/2 && a[i] <= a[j]))
                b[k] = a[i++];
            else
                b[k] = a[j++], cnt += i;
        for (size_t i=0; i<size; i++)
            a[i] = b[i];
        return cnt;
    }
}

int main()
{
    int t, n, a[1000], b[1000];
    for (cin >> t; t>0; t--) {
        cin >> n;
        for (int i=0; i<n; i++)
            cin >> a[i];
        
        int cnt = msort(a, n, b);
        cout << cnt << endl;
    }

    return 0;
}
