// #easy
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string statement;
    vector<uint32_t> stack;
    uint32_t prog_count;
    for (cin >> prog_count; prog_count > 0; --prog_count) {
        stack.assign(1, 1);
        while (cin >> statement && statement != "ENDPROGRAM") {
            if (statement == "IF" || statement == "ELSE")
                stack.push_back(1);
            else if (statement == "END_IF") {
                size_t sz = stack.size();
                stack[sz - 3] *= stack[sz - 2] + stack[sz - 1];
                stack.resize(sz - 2);
            }
        }
        cout << ((stack.back() == 0) ? (uint64_t(1) << 32) : stack.back()) << endl;
    }

    return 0;
}
