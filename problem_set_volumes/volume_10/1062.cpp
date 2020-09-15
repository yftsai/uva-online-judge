// #stack
#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
    uint32_t case_number = 1;
    for (string container_order; cin >> container_order && container_order != "end"; ++case_number) {
        set<char> stack_tops;
        for (const char c: container_order) {
            auto it = stack_tops.lower_bound(c);
            if (it == stack_tops.end())
                stack_tops.insert(it, c);
            else if (c != *it) {
                it = stack_tops.erase(it);
                stack_tops.insert(it, c);

            }
        }

        cout << "Case " << case_number << ": " << stack_tops.size() << endl;
    }
    return 0;
}
