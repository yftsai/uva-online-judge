// #easy
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string codes[16];
    for (int set_number = 1, code_count = 0; cin >> codes[code_count++]; ++set_number, code_count = 0) {
        while (cin >> codes[code_count] && codes[code_count] != "9")
            code_count++;
        sort(codes, codes + code_count);

        bool is_immed_decodable = true;
        for (int i = 0; is_immed_decodable && i < code_count - 1; ++i)
            if (codes[i].size() <= codes[i].size() && equal(codes[i].begin(), codes[i].end(), codes[i + 1].begin()))
                is_immed_decodable = false;
        cout << "Set " << set_number << " is" << (is_immed_decodable ? "" : " not") << " immediately decodable" << endl; 
    }

    return 0;
}
