// #tricky_input
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
    const int int_max = numeric_limits<int>::max();
    const string str_max = to_string(int_max);
    auto pred_digit = [](char c) { return isdigit(c); };
    auto pred_not_digit = [](char c) { return !isdigit(c); };

    string line;
    for (string line; getline(cin, line); ) {
        auto start = find_if(line.begin(), line.end(), pred_digit);
        auto end = find_if(start, line.end(), [](char c) { return !isdigit(c); });
        for (; *start == '0' && start + 1 != end; start++)
            ;
        string str_n(start, end);

        char op = *find_if(end, line.end(), [](char c) { return c == '+' || c == '*'; });

        start = find_if(end, line.end(), pred_digit);
        end = find_if(start, line.end(), pred_not_digit);
        for (; *start == '0' && start + 1 != end; start++)
            ;
        string str_m(start, end);

        int int_n = (str_n.size() < str_max.size() || (str_n.size() == str_max.size() && str_n <= str_max)) ? stoi(str_n) : -1;
        int int_m = (str_m.size() < str_max.size() || (str_m.size() == str_max.size() && str_m <= str_max)) ? stoi(str_m) : -1;

        cout << line << endl;
        if (int_n < 0)
            cout << "first number too big" << endl;
        if (int_m < 0)
            cout << "second number too big" << endl;
        if ((int_n < 0 && int_m != 0)
            || (int_n != 0 && int_m < 0)
            || (int_n > 0 && int_m > 0 && ((op == '+' && int_max - int_n < int_m) || (op == '*' && int_max / int_n < int_m))))
            cout << "result too big" << endl;
    }
	return 0;
}
