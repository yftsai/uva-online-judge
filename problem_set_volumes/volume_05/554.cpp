// #easy
#include <iostream>
#include <string>
#include <set>
using namespace std;

char shift(char c)
{
    c = (c == ' ') ? 0 : (c - 'A' + 1);
    c = (c + 1) % 27;
    return (c == 0) ? ' ' : (c - 1 + 'A');
}

uint16_t score(const set<string> &dictionary, const string &text, string &decrypted_text)
{
    string word;
    uint16_t score = 0;
    uint16_t last_line_length = 0;

    decrypted_text.clear();
    for (size_t p = text.find_first_not_of(' '), q, x = 0;
        p < text.size();
        p = text.find_first_not_of(' ', q), x++) {
        q = text.find(' ', p);
        word = text.substr(p, q - p);

        if (dictionary.find(word) != dictionary.end())
            score++;

        if (last_line_length > 0 && last_line_length + 1 + word.size() > 60) {
            decrypted_text += "\n";
            last_line_length = 0;
        }
        decrypted_text   += (last_line_length > 0 ? " " : "") + word;
        last_line_length += (last_line_length > 0 ? 1   : 0)  + word.size();
    }
    return score;
}

int main()
{
    string line;
    set<string> dictionary;
    while (getline(cin, line) && line != "#")
        dictionary.insert(line);

    string decrypted_text, best_decrypted_text;
    while (getline(cin, line)) {
        uint16_t best_score = score(dictionary, line, best_decrypted_text);
        for (uint16_t i = 0; i < 26; i++) {
            for (char &c: line)
                c = shift(c);

            const uint16_t s = score(dictionary, line, decrypted_text);
            if (s > best_score) {
                best_score = s;
                best_decrypted_text = decrypted_text;
            }
        }

        cout << best_decrypted_text << endl;
    }

    return 0;
}
