#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    for (int n; cin >> n && n != 0; ) {
        vector<int> t(n), b(n);
        for (int i=0; i<n; ++i)
            cin >> t[i] >> b[i];

        int min_time = 0;
        multiset<int, std::greater<int>> pq;
        for (int i=n-1; i>=0; pq.insert(t[i--]))
            for (; b[i]>0 && pq.size()>0; --b[i], pq.erase(pq.begin()))
                min_time += *pq.begin()/2;
        
        for (auto &t: pq)
            min_time += t;

        cout << min_time << endl;
    }
    return 0;
}
