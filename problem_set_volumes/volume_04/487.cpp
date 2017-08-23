// #priority_queue
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int case_count, n;
    for (cin >> case_count; case_count > 0; case_count--) {
        cin >> n;
        vector<char> table(n * n);
        for (int i = 0; i < n * n; i++)
            cin >> table[i];

        typedef pair<string, int> state;
        auto cmp = [](const state &p, const state &q) {
            if (q.first.size() != p.first.size())
                return q.first.size() < p.first.size();
            else if (q.first != p.first)
                return q.first < p.first;
            else
                return q.second < p.second;
        };
        priority_queue<state, vector<state>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < n * n; i++)
            pq.push(state(string(1, table[i]), i));

        string previous;
        while (!pq.empty()) {
            const state s = pq.top();
            pq.pop();
            if (s.first.size() >= 3)
                if (previous != s.first)
                    cout << (previous = s.first) << endl;

            for (int i = max(0, s.second/n - 1); i <= min(n - 1, s.second/n + 1); i++)
                for (int j = max(0, s.second % n - 1); j <= min(n - 1, s.second % n + 1); j++)
                    if (s.first.back() < table[n * i + j])
                        pq.push(state(s.first + table[n * i + j], n * i + j));
        }
        if (case_count > 1)
            cout << endl;
    }
    return 0;
}
