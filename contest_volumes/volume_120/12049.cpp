// #trivial
#include <iostream>
#include <unordered_set>
using namespace std;

int main()
{
    uint16_t t, n, m;
    unordered_multiset<int32_t> elements;
    for (cin >> t; t > 0 && cin >> n >> m; t--, elements.clear()) {
        int32_t element;
        for (uint16_t i = 0; i < n && cin >> element; i++)
            elements.insert(element);

        uint16_t remove_count = 0;
        for (uint16_t i = 0; i < m && cin >> element; i++) {
            auto it = elements.find(element);
            if (it == elements.end())
                remove_count++;
            else
                elements.erase(it);
        }

        cout << elements.size() + remove_count << endl;
    }

    return 0;
}
