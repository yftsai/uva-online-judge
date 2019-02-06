#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    vector<char> operations;
    vector<char> stack;
    for (string source, target; cin >> source >> target; operations.clear()) {
        operations.assign(source.size(), 'i');
        operations.resize(source.size() + target.size(), 'o');

        stack.clear();
        uint32_t i = 0, j = 0, k = 0;
        cout << "[" << endl;
        do {
            for (; k < operations.size(); ++k)
                if (operations[k] == 'i')
                    stack.push_back(source[i++]);
                else if (stack.size() > 0 && stack.back() == target[j])
                    stack.pop_back(), ++j;
                else
                    break;

            if (j == target.size()) {
                cout << operations.front();
                for (uint32_t i = 1u; i < k; ++i)
                    cout << " " << operations[i];
                cout << endl;
            }

            sort(operations.begin() + k, operations.end(), greater<char>());
            for (; k > 0 && operations[k - 1u] == 'o'; --k)
                stack.push_back(target[--j]);
            if (k > 0)
                stack.pop_back(), --i, --k;
        } while (next_permutation(operations.begin() + k, operations.end()));
        cout << "]" << endl;
    }

    return 0;
}
