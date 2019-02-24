#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t n;
    cin >> n;

    vector<string> dictionary(n);
    unordered_map<string, uint16_t> word_indexes;
    unordered_map<string, set<uint16_t>> shortened_word_indexes;
    string shortened_word;
    for (uint16_t i = 0; i < n && cin >> dictionary[i]; ++i) {
        word_indexes.emplace(dictionary[i], i);
        shortened_word = dictionary[i].substr(1u);
        for (uint16_t j = 0; j < dictionary[i].size(); ++j) {
            shortened_word_indexes[shortened_word].insert(i);
            if (j < shortened_word.size())
                shortened_word[j] = dictionary[i][j];
        }
    }

    uint16_t q;
    string word;
    for (cin >> q; q > 0 && cin >> word; --q) {
        if (word_indexes.find(word) != word_indexes.end())
            cout << word << " is correct" << endl;
        else {
            uint16_t index = n;

            // one letter is missing
            auto swi_it = shortened_word_indexes.find(word);
            if (swi_it != shortened_word_indexes.end())
                index = *swi_it->second.begin();

            shortened_word = word.substr(1u);
            for (uint16_t i = 0; i < word.size(); ++i) {
                // one letter more
                auto wi_it = word_indexes.find(shortened_word);
                index = min(index, (wi_it != word_indexes.end()) ? wi_it->second : n);

                // one character wrong
                swi_it = shortened_word_indexes.find(shortened_word);
                if (swi_it != shortened_word_indexes.end())
                    for (uint16_t j: swi_it->second)
                        if (j >= index)
                            break;
                        else if (word.size() == dictionary[j].size()) {
                            auto p = mismatch(word.begin(), word.end(), dictionary[j].begin());
                            if (mismatch(++p.first, word.end(), ++p.second).first == word.end())
                                index = j;
                        }

                // incorrect order
                if (i + 1u < word.size()) {
                    swap(word[i], word[i + 1u]);
                    wi_it = word_indexes.find(word);
                    index = min(index, (wi_it != word_indexes.end()) ? wi_it->second : n);
                    swap(word[i], word[i + 1u]);
                }

                if (i < shortened_word.size())
                    shortened_word[i] = word[i];
            }

            if (index < n)
                cout << word << " is a misspelling of " << dictionary[index] << endl;
            else
                cout << word << " is unknown" << endl;
        }
    }

    return 0;
}
