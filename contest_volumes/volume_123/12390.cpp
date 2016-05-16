#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

int get_max_assignment(int p, int b)
{
    return p/b + (p%b==0 ? 0 : 1);
}

int main()
{
    for (int n, b; cin >> n >> b && n != -1; ) {
        priority_queue<tuple<int, int, int>> pq;    // max assignment to a box, n people, n boxes
        for (int i=0, a; i<n && cin >> a; ++i)
            pq.push(make_tuple(a, a, 1));
        for (b-=n; b>0; ) {
            auto c = pq.top();
            pq.pop();
            auto p = pq.empty() ? 0 : get<0>(pq.top());
            for (; b>0 && get<0>(c) >= p; --b)
                get<0>(c) = get_max_assignment(get<1>(c), ++get<2>(c));
            pq.push(c);
        }
        cout << get<0>(pq.top()) << endl;
    }
    return 0;
}
