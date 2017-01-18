//#dynamic_programming
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

void get_min_length(const string &seq, const size_t start, const size_t length, vector<vector<int>> &table)
{
    int &t = table[start][length];
    if (length == 0)
        t = 0;
    else if (t < numeric_limits<int>::max())
        ;
    else if (seq[start] == ')' || seq[start] == ']') {
        get_min_length(seq, start + 1, length - 1, table);
        t = table[start + 1][length - 1] + 2;
    }
    else {
        const char c = (seq[start] == '(') ? ')' : ']';
        for (size_t i = start + 1; i <= start + length; ++i) {
            const bool is_matched = (i < start + length && seq[i] == c);
            const size_t start1 = start + 1, len1 = i - start - 1;
            const size_t start2 = i + (is_matched ? 1 : 0);
            const size_t len2 = length + start - i - (is_matched ? 1 : 0);
            get_min_length(seq, start1, len1, table);
            get_min_length(seq, start2, len2, table);
            t = min(t, table[start1][len1] + table[start2][len2] + 2);
        }
    }
}

string get_reg_seq(const string &seq, const size_t start, const size_t length, const vector<vector<int>> &table)
{
    if (length == 0 || table[start][length] == 0)
        return "";
    else if (seq[start] == ')' || seq[start] == ']')
        return (seq[start] == ')' ? "()" : "[]") + get_reg_seq(seq, start + 1, length - 1, table);
    else {
        const char c = (seq[start] == '(') ? ')' : ']';
        for (size_t i = start + 1; i <= start + length; ++i) {
            const bool is_matched = (i < start + length && seq[i] == c);
            const size_t start1 = start + 1, len1 = i - start - 1;
            const size_t start2 = i + (is_matched ? 1 : 0);
            const size_t len2 = length + start - i - (is_matched ? 1 : 0);
            if (table[start1][len1] + table[start2][len2] + 2 == table[start][length])
                return seq[start] + get_reg_seq(seq, start1, len1, table) + c + get_reg_seq(seq, start2, len2, table);
        }
        return "unreachable";
    }
}

int main()
{
    string line;
    getline(cin, line);
    for (int n = stoi(line); n > 0; n--) {
        getline(cin, line);
        getline(cin, line);

        vector<vector<int>> table(line.size() + 1);
        for (size_t i = 0; i < table.size(); ++i)
            table[i].resize(line.size() - i + 1, numeric_limits<int>::max());

        get_min_length(line, 0, line.size(), table);
        cout << get_reg_seq(line, 0, line.size(), table) << endl;
        if (n>1)
            cout << endl;
    }
    return 0;
}
