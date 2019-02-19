// #string_search
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    uint32_t n;
    uint16_t k, w;
    string current_word, next_word;
    vector<uint16_t> eq_lens(1, 0);
    for (cin >> n; n > 0 && cin >> k >> w; --n) {
        uint32_t letter_count = k;
        cin >> current_word;
        for (--w; w > 0 && cin >> next_word; --w, swap(current_word, next_word)) {
            eq_lens.resize(k);
            for (uint16_t i = 1; i < k; ++i) {
                auto &len = eq_lens[i];
                for (len = eq_lens[i - 1u]; len != 0 && next_word[len] != next_word[i]; len = eq_lens[len - 1u])
                    ;
                if (next_word[len] == next_word[i])
                    ++len;
            }

            uint16_t len = 0;
            for (uint16_t i = 0; i < k; ++i) {
                for (; len != 0 && current_word[i] != next_word[len]; len = eq_lens[len - 1u])
                    ;
                if (current_word[i] == next_word[len])
                    ++len;
            }
            letter_count += k - len;
        }
        cout << letter_count << endl;
    }

    return 0;
}
