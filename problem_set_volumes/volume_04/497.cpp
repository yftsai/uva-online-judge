// #longest_increasing_subsequence
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    string line;
    getline(cin, line);
    int case_count = stoi(line);
    getline(cin, line);

    for (; case_count > 0; case_count--){
        vector<int> seq, preds, backs;
        auto cmp = [&](int i, int j) { return seq[i] < seq[j]; };

        while (getline(cin, line) && line[0] != '\0') {
            seq.push_back(stoi(line));
            auto it = lower_bound(backs.begin(), backs.end(), seq.size() - 1, cmp);
            if (it == backs.end()) {
                if (it == backs.begin()) {
                    preds.push_back(-1);
                    backs.push_back(0);
                }
                else {
                    preds.push_back(*prev(it));
                    backs.push_back(seq.size() - 1);
                }
            }
            else {
                preds.push_back(it == backs.begin() ? -1 : *prev(it));
                *it = seq.size() - 1;
            }
        }

        vector<int> lis;
        for (int p = backs.back(); p >= 0; p = preds[p])
            lis.push_back(seq[p]);
        cout << "Max hits: " << lis.size() << endl;
        for (auto it = lis.rbegin(); it != lis.rend(); it++)
            cout << *it << endl;
        if (case_count > 1)
            cout << endl;
    }
    return 0;
}
