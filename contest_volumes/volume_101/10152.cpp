#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    vector<string> stack, order;
    string line;
    getline(cin, line);
    for (uint32_t k = stoi(line); k > 0 && getline(cin, line); --k) {
        stack.resize(stoi(line));
        for (string &t: stack)
            getline(cin, t);

        order.resize(stack.size());
        for (string &t: order)
            getline(cin, t);

        auto order_it = order.rbegin();
        for (auto it = stack.rbegin(); it != stack.rend(); ++it)
            if (*order_it == *it)
                ++order_it;
        for (; order_it != order.rend(); ++order_it)
            cout << *order_it << endl;
        cout << endl;
    }

    return 0;
}
