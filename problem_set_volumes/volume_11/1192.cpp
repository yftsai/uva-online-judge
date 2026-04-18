// #dynamic_programming
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string query;
    getline(cin, query);
    getline(cin, query);
    cout << "The query sequence is:" << endl;
    cout << query << endl;
    cout << endl;

    string seq;
    vector<int> rows[2];
    vector<string> seqs;
    int score = 0;

    while (getline(cin, seq) && getline(cin, seq) && getline(cin, seq)) {
        const string &s = query.size() <= seq.size() ? query : seq;
        const string &t = query.size() <= seq.size() ? seq : query;

        rows[0].clear();
        for (size_t sz = 0; sz <= s.size(); sz++)
            rows[0].push_back(-7 * sz);
        for (size_t i = 0; i < t.size(); i++, rows[0].swap(rows[1])) {
            rows[1].clear();
            rows[1].push_back(rows[0][0] - 7);
            for (size_t j = 0; j < s.size(); j++) {
                if (s[j] == t[i])
                    rows[1].push_back(rows[0][j] + 5);
                else
                    rows[1].push_back(max({ rows[0][j] - 4,
                                            rows[0][j + 1] - 7,
                                            rows[1][j] - 7 }));
            }
        }

        if (seqs.size() == 0 || rows[0].back() > score) {
            score = rows[0].back();
            seqs.resize(1);
            seqs[0].swap(seq);
        }
        else if (rows[0].back() == score)
            seqs.emplace_back(seq);
    }

    cout << "The most similar sequences are:" << endl;
    for (auto &s: seqs) {
        cout << endl;
        cout << s << endl;
        cout << "The similarity score is: " << score << endl;
    }

    return 0;
}
