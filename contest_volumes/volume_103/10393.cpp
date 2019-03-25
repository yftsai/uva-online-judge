// #easy
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    const string chars[] = {
        "qaz",
        "wsx",
        "edc",
        "rfvtgb",
        " ",
        " ",
        "yhnujm",
        "ik,",
        "ol.",
        "p;/"
    };

    string word;
    for (uint16_t f, n; cin >> f >> n; ) {
        set<char> untypeable_chars;
        for (uint16_t finger; f > 0 && cin >> finger; --f)
            untypeable_chars.insert(chars[finger - 1].begin(), chars[finger - 1].end());
        auto is_typeable = [&untypeable_chars](char c) {
            return untypeable_chars.find(c) == untypeable_chars.end();
        };

        set<string> longest_words;
        for (; n > 0 && cin >> word; --n)
            if ((longest_words.size() == 0 || word.size() >= longest_words.begin()->size())
                && all_of(word.begin(), word.end(), is_typeable)) {
                if (longest_words.size() > 0 && word.size() > longest_words.begin()->size())
                    longest_words.clear();
                longest_words.emplace(move(word));
            }

        cout << longest_words.size() << endl;
        for (auto &w: longest_words)
            cout << w << endl;
    }
    return 0;
}
