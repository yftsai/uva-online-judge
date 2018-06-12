// #huffman_coding
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main()
{
    priority_queue<uint32_t, std::vector<uint32_t>, greater<int>> q;
    for (int n; cin >> n && n != 0; q.pop()) {
        for (uint32_t m; n > 0 && cin >> m; n--)
            q.push(m);

        uint32_t cost = 0;
        while (q.size() > 1) {
            uint32_t a = q.top();
            q.pop();
            uint32_t b = q.top();
            q.pop();
            cost += a + b;
            q.push(a + b);
        }
        cout << cost << endl;
    }
    return 0;
}
