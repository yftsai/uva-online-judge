#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#define LEN 1024

bool visit_partition(int sq[], int n, int i, int j)
{
    const int visited = -1;
    if (sq[i*n+j] == visited)
        return false;
    else {
        int v = sq[i*n+j];
        const int di[] = {1, -1, 0, 0};
        const int dj[] = {0, 0, 1, -1};
        sq[i*n+j] = visited;
        for (int k=0; k<4; k++){
            int ii = i+di[k];
            int jj = j+dj[k];
            if (0<=ii && ii<n && 0<=jj && jj<n && sq[ii*n+jj]==v)
                visit_partition(sq, n, ii, jj);
        }

        return true;
    }
}

int main()
{
    int n;
    char line[LEN];
    int square[10000];

    while (true){
        cin.getline(line, LEN);
        stringstream(line) >> n;
        if (n==0)
            break;
       
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                square[i*n+j] = 0;

        for (int k=1; k<n; k++){
            int i, j;
            stringstream ss;
            cin.getline(line, LEN);
            ss.str(line);
            while (ss >> i >> j)
                square[(i-1)*n+j-1] = k;
        }

        int par = 0;
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                if (visit_partition(square, n, i, j))
                    par++;
        cout << (par==n ? "good" : "wrong") << endl;
    }

    return 0;
}
