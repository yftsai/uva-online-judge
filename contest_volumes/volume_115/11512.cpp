// #string_search
// It will be more efficient to use a suffix tree.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    uint16_t t;
    string sequence, substring;
    vector<uint16_t> lengths;
    for (cin >> t; t > 0 && cin >> sequence; --t) {
        substring = "";

        for (uint16_t i = 0; i < sequence.size(); ++i) {
            lengths.resize(sequence.size() - i);
            lengths[0] = 0;
            for (uint16_t j = 1; i + j < sequence.size(); ++j) {
                uint16_t &len = lengths[j];
                for (len = lengths[j - 1u]; len > 0 && sequence[i + len] != sequence[i + j]; len = lengths[len - 1u])
                    ;
                if (sequence[i + len] == sequence[i + j])
                    ++len;
                if (len > substring.size() || (len == substring.size() && sequence.compare(i, len, substring.c_str(), len) < 0))
                    substring = sequence.substr(i, len);
            }
        }

        if (substring.size() == 0)
            cout << "No repetitions found!" << endl;
        else {
            uint16_t repetition_count = 0;
            for (uint16_t i = 0; i + substring.size() <= sequence.size(); ++i)
                if (substring.compare(0, substring.size(), sequence.c_str() + i, substring.size()) == 0)
                    ++repetition_count;
            cout << substring << " " << repetition_count << endl;
        }
    }
    return 0;
}
