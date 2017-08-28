// #easy
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int case_count;

    for (cin >> case_count; case_count > 0; case_count--) {
        int m, w;
        cin >> m >> w;
        priority_queue<int> weights;
        for (int i = 0, sum = 0, weight; i < m && cin >> weight; i++)
            if (sum + weight <= w) {
                sum += weight;
                weights.push(weight);
            }
            else if (weights.size() > 0 && weight < weights.top()) {
                sum = sum - weights.top() + weight;
                weights.pop();
                weights.push(weight);
            }
        cout << weights.size() << endl;
    }

    return 0;
}
