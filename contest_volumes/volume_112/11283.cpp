// #easy
#include <iostream>
#include <string>
using namespace std;

bool match(const int16_t row, const int16_t col, const char *word, char board[4][5])
{
    if (word[0] == '\0')
        return true;
    else if (word[0] != board[row][col])
        return false;
    else {
        const char matched_char = board[row][col];
        board[row][col] = '\0';

        bool is_word_matched = false;
        for (int16_t r = max(row - 1, 0); r <= min(row + 1, 3) && !is_word_matched; ++r)
            for (int16_t c = max(col - 1, 0); c <= min(col + 1, 3) && !is_word_matched; ++c)
                is_word_matched = match(r, c, word + 1, board);

        board[row][col] = matched_char;
        return is_word_matched;
    }
}

int main()
{
    const uint16_t points[] = { 1, 1, 2, 3, 5, 11 };
    char board[4][5];
    string word;

    uint32_t n;
    cin >> n;
    for (uint32_t game_number = 1; game_number <= n; ++game_number) {
        for (uint16_t i = 0; i < 4; ++i)
            cin >> board[i];

        uint16_t m;
        cin >> m;
        uint16_t score = 0;
        for (uint16_t i = 0; i < m; ++i) {
            cin >> word;
            bool is_word_matched = false;
            for (uint16_t r = 0; r < 4 && !is_word_matched; ++r)
                for (uint16_t c = 0; c < 4 && !is_word_matched; ++c)
                    is_word_matched = match(r, c, word.c_str(), board);

            if (is_word_matched)
                score += points[min<uint16_t>(word.size(), 8) - 3];
        }

        cout << "Score for Boggle game #" << game_number << ": " << score << endl;
    }
    return 0;
}
