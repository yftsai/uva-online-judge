// #greedy
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
using namespace std;

void trim_front(const vector<uint32_t> &words, uint32_t &i, unordered_multiset<uint32_t> &ws)
{
    while (true) {
        auto it = ws.find(words[i]);
        ws.erase(it);

        if (ws.find(words[i]) != ws.end())
            i++;
        else {
            ws.insert(words[i]);
            break;
        }
    }
}

int main()
{
    string line;
    getline(cin, line);
    const uint16_t t = stoi(line);

    unordered_map<string, uint32_t> indexes;
    vector<uint32_t> words;
    unordered_multiset<uint32_t> ws;

    for (uint16_t d = 1, x = 0; d <= t && getline(cin, line); x++) {
        if (line != "END") {
            string::iterator b, e = line.begin();
            while ((b = find_if(e, line.end(), [](char c) { return islower(c); })) != line.end()) {
                e = find_if(b, line.end(), [](char c) { return !islower(c); });
                const auto it = indexes.emplace(string(b, e), indexes.size()).first;
                words.emplace_back(it->second);
            }
        }
        else {
            const uint32_t kind_count = indexes.size();

            ws.clear();
            uint32_t j = 0, k = 0;
            for (j = 0; j < words.size() && k < kind_count; j++) {
                k += (ws.find(words[j]) == ws.end()) ? 1 : 0;
                ws.insert(words[j]);
            }

            uint32_t i = 0;
            trim_front(words, i, ws);
            pair<uint32_t, uint32_t> pq(i + 1, j);
            uint32_t dpq = j - i;

            for (; j < words.size(); j++) {
                ws.insert(words[j]);
                trim_front(words, i, ws);
                if (j + 1 - i < dpq) {
                    pq.first = i + 1;
                    pq.second = j + 1;
                    dpq = j + 1 - i;
                }
            }

            cout << "Document " << d << ": " << pq.first << " " << pq.second << endl;
            d++;
            indexes.clear();
            words.clear();
            ws.clear();
        }
    }

    return 0;
}
