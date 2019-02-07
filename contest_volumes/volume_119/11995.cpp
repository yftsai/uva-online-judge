// #trivial
#include <iostream>
#include <queue>
#include <stack>
#include <set>
using namespace std;

int main()
{
    for (int n; cin >> n; ) {
        stack<int> s;
        queue<int> q;
        multiset<int> pq;
        bool is_stack = true, is_queue = true, is_pq = true;

        for (int i = 0, op, x; i < n && cin >> op >> x; ++i) {
            if (op == 1) {
                if (is_stack)
                    s.push(x);
                if (is_queue)
                    q.push(x);
                if (is_pq)
                    pq.insert(x);
            }
            else {
                if (is_stack && s.size() > 0 && s.top() == x)
                    s.pop();
                else
                    is_stack = false;

                if (is_queue && q.size() > 0 && q.front() == x)
                    q.pop();
                else
                    is_queue = false;

                if (is_pq && pq.size() > 0 && *pq.rbegin() == x)
                    pq.erase(--pq.end());
                else
                    is_pq = false;
            }
        }

        if (is_stack && !is_queue && !is_pq)
            cout << "stack" << endl;
        else if (!is_stack && is_queue && !is_pq)
            cout << "queue" << endl;
        else if (!is_stack && !is_queue && is_pq)
            cout << "priority queue" << endl;
        else if (!is_stack && !is_queue && !is_pq)
            cout << "impossible" << endl;
        else
            cout << "not sure" << endl;
    }

    return 0;
}
