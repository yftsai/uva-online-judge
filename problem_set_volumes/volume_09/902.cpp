// #easy
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct string_view
{
    const char *view;
    uint8_t length;

    string_view(const char *v, uint8_t len):
        view(v),
        length(len) {}

    bool operator<(const string_view &sv) const
    {
        for (uint8_t i = 0; i < length && i < sv.length; ++i)
            if (view[i] != sv.view[i])
                return view[i] < sv.view[i];
        return length < sv.length;
    }
};

int main()
{
    uint16_t n;
    string message;

    while (cin >> n >> message) {
        map<string_view, uint32_t> counts;
        uint32_t max_count = 0;
        string_view password(message.c_str(), n);
        for (unsigned int i = 0; i + n <= message.size(); ++i){
            string_view sv(message.c_str() + i, n);
            auto it = counts.lower_bound(sv);
            if (it == counts.end() || sv < it->first)
                it = counts.emplace_hint(it, sv, 0);

            if ((++it->second) > max_count) {
                password = sv;
                max_count = it->second;
            }
        }
        cout << string(password.view, n) << endl;
    }

    return 0;
}
