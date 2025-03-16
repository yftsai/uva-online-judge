// #tricky_input
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<string> init;
    string card, word;

    for (uint16_t n; cin >> n && n > 0; init.clear()) {
        init.resize(n);
        uint16_t p = n - 1;
        for (uint16_t i = 0; i < n; i++) {
            cin >> card >> word;

            for (uint16_t j = 0; j < word.size(); j++)
                do {
                    p = (p + 1) % n;
                } while (!init[p].empty());
            init[p].swap(card);
        }

        card.swap(init.back());
        init.pop_back();
        for (auto &c: init)
            cout << c << " ";
        cout << card << endl;
    }

    return 0;
}
