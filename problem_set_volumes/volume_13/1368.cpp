// #easy
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    const string ns = "ACGT";   // in lexical order

    uint32_t t;
    uint16_t m, n;
    vector<string> seqs;
    for (cin >> t; t > 0 && cin >> m >> n; t--) {
        seqs.resize(m);
        for (auto &s: seqs)
            cin >> s;

        uint16_t error = 0;
        for (uint16_t i = 0; i < seqs.front().size(); i++) {
            uint16_t counts[4] = { 0 };
            for (uint16_t j = 0; j < seqs.size(); j++)
                for (uint16_t k = 0; k < ns.size(); k++)
                    if (seqs[j][i] == ns[k])
                        counts[k]++;

            uint16_t max_c = 0;
            char c;
            for (uint16_t k = 0; k < ns.size(); k++)
                if (counts[k] > max_c) {
                    max_c = counts[k];
                    c = ns[k];
                }
            error += m - max_c;
            cout << c;
        }
        cout << endl;

        cout << error << endl;
    }

    return 0;
}
