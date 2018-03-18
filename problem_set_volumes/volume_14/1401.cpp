// #dynamic_programming
#include <iostream>
#include <string>
#include <memory>
#include <map>
using namespace std;

struct trie
{
    map<char, unique_ptr<trie>> children;
};

int main()
{
    const int stick_count = 20071027;
    string word, w;
    unique_ptr<int[]> counts(new int[300001]);

    for (uint32_t case_number = 1, s; cin >> word >> s; case_number++) {
        trie t;
        for (uint32_t i = 0; i < s && cin >> w; i++) {
            trie *p = &t;
            for (char c: w) {
                unique_ptr<trie> &child = p->children[c];
                if (child == nullptr)
                    child.reset(new trie());
                p = child.get();
            }
            p->children['\0'] = nullptr;
        }

        counts[word.size()] = 1;
        for (size_t i = word.size(); i > 0; i--) {
            counts[i - 1] = 0;
            trie *p = &t;
            for (size_t j = i - 1; j < word.size() && p != nullptr; j++) {
                auto it = p->children.find(word[j]);
                if (it == p->children.end())
                    p = nullptr;
                else {
                    p = it->second.get();
                    if (p->children.find('\0') != p->children.end())
                        counts[i - 1] = (counts[i - 1] + counts[j + 1]) % stick_count;
                }
            }
        }

        cout << "Case " << case_number << ": " << counts[0] << endl;
    }

    return 0;
}
