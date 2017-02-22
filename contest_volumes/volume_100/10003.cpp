// #dynamic_programming
#include <iostream>
using namespace std;

int cost[100][100];
int section[100];

int getCost(int start, int end)
{
    int i;
    if (cost[start][end]!=-1)
        ;
    else if (start+1==end)
        cost[start][end]=0;
    else {
        cost[start][end]=getCost(start, start+1) + getCost(start+1, end)+section[end]-section[start];
        for (i=start+2; i<end; i++)
            cost[start][end]=min(cost[start][end], getCost(start, i) + getCost(i, end)+section[end]-section[start]);
    }
    return cost[start][end];
}

int main()
{
    int l, n;
    int i, j;
    while ((cin >> l) && l!=0){
        cin >> n;
        for (i=1; i<=n; i++)
            cin >> section[i];
        section[n+1]=l;
        for (i=0; i<=n+2; i++)
            for (j=i; j<=n+2; j++)
                cost[i][j]=-1;
        cout << "The minimum cutting is " << getCost(0, n+1) << "." << endl;
    }
    return 0;
}
