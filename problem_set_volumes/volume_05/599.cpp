// #parsing
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    uint8_t set_ids[26];
    const uint8_t unknown = 26;
    auto get_set_id = [&set_ids](uint8_t p) {
        if (set_ids[p] == unknown)
            set_ids[p] = p;
        uint8_t s = p;
        for (; set_ids[s] != s; s = set_ids[s])
            ;
        for (uint8_t q = p, r; set_ids[q] != q; q = r) {
            r = set_ids[q];
            set_ids[q] = s;
        }
        return s;
    };

    uint32_t test_count;
    for (cin >> test_count; test_count > 0; --test_count) {
        fill(set_ids, set_ids + 26, unknown);
        char lookahead;
        while (cin >> lookahead && lookahead == '(') {
            char p, q;
            cin >> p >> q;
            cin >> q;
            set_ids[get_set_id(p - 'A')] = get_set_id(q - 'A');
            cin >> q;
        }

        while (cin >> lookahead && lookahead == '*')
            ;
        cin.putback(lookahead);

        uint16_t tree_count = 0, acorn_count = 0;
        while (cin >> lookahead)
            if (lookahead == '(') {
                cin.putback(lookahead);
                break;
            }
            else {
                if (set_ids[lookahead - 'A'] == unknown)
                    ++acorn_count;
                else if (set_ids[lookahead - 'A'] == lookahead - 'A')
                    ++tree_count;
                cin >> lookahead;
                if (lookahead != ',') {
                    cin.putback(lookahead);
                    break;
                }
            }
        cout << "There are " << tree_count << " tree(s) and " << acorn_count << " acorn(s)." << endl;
    }
    return 0;
}
