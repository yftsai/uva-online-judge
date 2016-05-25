// #trivial
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    const vector<string> braille({
        ".***..",
        "*.....",
        "*.*...",
        "**....",
        "**.*..",
        "*..*..",
        "***...",
        "****..",
        "*.**..",
        ".**..."
    });

    for (int d; cin >> d && d>0; ) {
        char c;
        vector<string> message, translation;

        cin >> c;
        message.resize((c == 'S') ? 1 : d*3);
        for (auto &m: message)
            cin >> m;

        translation.resize((c == 'S') ? 3 : 1);
        if (c == 'S')
            for (auto c: message[0])
                for (size_t i=0; i<translation.size(); ++i)
                    translation[i] += (translation[i].empty() ? "" : " ") + braille[c-'0'].substr(2*i, 2);
        else
            for (int i=0; i<d; ++i) {
                string m = message[i] + message[i+d] + message[i+d+d];
                translation[0] += char('0' + find(braille.begin(), braille.end(), m) - braille.begin());
            }

        for (auto &t: translation)
            cout << t << endl;
    }

    return 0;
}
