#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    unsigned int n, k, b;
    
    while ((cin >> n) && (n>0)){
        vector<unsigned int> bill;
        unsigned long amount = 0;
        for (unsigned int i=0; i<n; i++){
            cin >> k;
            for (unsigned int j=0; j<k; j++){
                cin >> b;
                bill.push_back(b);
            }
            sort(bill.begin(), bill.end());
            if (bill.size()>2*n)
               bill.erase(bill.begin()+n, bill.end()-n);
            amount += *(--bill.end()) - *bill.begin();
            bill.erase(bill.begin());
            bill.erase(--bill.end());
        }
        cout << amount << endl;
    }
   
    return 0;
}
